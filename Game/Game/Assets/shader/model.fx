/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

cbuffer LightParam : register(b10)
{
	float3 eyepos;
	int numDirectionLight;
}



/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////

/*!
 * @brief	ディレクションライト用の構造体。
 */
struct SDirectionLight {
	float4 color;			//!<ライトのカラー。
	float3 direction;		//!<ライトの方向。
};

StructuredBuffer <SDirectionLight>DirectionLightSB:register(t100);
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float4 posInLVP		: TEXCOORD1;	//ライトビュープロジェクション空間での座標。
	float3 worldPos	: TEXCOORD2;	//ワールド座標。
};
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//ローカル座標系からワールド座標系に変換する。
	float4 pos = mul(mWorld, In.Position);
	//ワールド座標をピクセルシェーダーに渡す。
	psInput.worldPos = pos.xyz;
	//ワールド座標系からカメラ座標系に変換する。
	pos = mul(mView, pos);
	//カメラ座標系からスクリーン座標系に変換する。
	pos = mul(mProj, pos);
	psInput.Position = pos;

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}
	psInput.worldPos = pos.xyz;
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;

	psInput.TexCoord = In.TexCoord;
    return psInput;
}

/// <summary>
/// ラインバート拡散反射を計算する。
/// </summary>
float3 CalcDiffuseLight(float3 normal)
{
	float3 lig = 0.0f;
	//numDirectionLightvの値が取れていない。
	//for (int i = 0; i < numDirectionLight; i++) {
	//とりあえず。一本で当ててる。
	for (int i = 0; i < numDirectionLight; i++) {
		//ランバート拡散反射。
		lig += max(0.5f, dot(normal * -1.0f, DirectionLightSB[i].direction)) * DirectionLightSB[i].color;
	}
	return lig;
}
float3 Toon(float3 normal)
{

}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);


	float3 lig = 0.0f;
	//ラインバート拡散反射
	//lig += CalcDiffuseLight(In.Normal);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	//finalColor.xyz = albedoColor.xyz * lig;

	{
		for (int i = 0; i < numDirectionLight; i++) {
			//2階調の陰影を求める。
			//ライトの方向と法線の内積を取るとライトの強さが求まる。
			//強さが一定値以下(今回は0.2)なら暗いテクスチャを使う。
			//それ以上なら明るいテクスチャを使う。
			float3 color = 0.0f;
			if (dot(-DirectionLightSB[i].direction, In.Normal) < 0.1f) {
				color = albedoColor.xyz * 0.5f;
			}
			else {
				color = albedoColor.xyz * 1.0f;
			}
			//リムを当てる。
			float3 eyeDir = normalize(eyepos - In.worldPos);
			float lim = (1.0f - dot(-In.Normal, eyeDir)) * 1.0f;								//カメラの方向と垂直な場合逆光の強さが強くなる。
			lim *= max(0.0f, dot(eyeDir, -DirectionLightSB[i].direction));						//完全に逆行していたらbaseLimの値がそのままでる。
			if (lim > 0.85f) {
				//逆光が発生している。
				color = albedoColor.xyz;
			}
			finalColor = float4(color.xyz, 1.0f);
		}
	}

	return finalColor;
}