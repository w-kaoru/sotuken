/*!
 * @brief	���f���V�F�[�_�[�B
 */


 /////////////////////////////////////////////////////////////
 // Shader Resource View
 /////////////////////////////////////////////////////////////
 //�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);
Texture2D<float4> shadowMap : register(t1);		//todo �V���h�E�}�b�v�B
Texture2D<float4> lightTexture : register(t10);
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
};

/// <summary>
/// �V���h�E�}�b�v�p�̒萔�o�b�t�@�B
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
}


cbuffer LightParam : register(b10)
{
	float3 eyepos;
	int numDirectionLight;
}


/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////

/*!
 * @brief	�f�B���N�V�������C�g�p�̍\���́B
 */
struct SDirectionLight {
	float4 color;			//!<���C�g�̃J���[�B
	float3 direction;		//!<���C�g�̕����B
};

StructuredBuffer <SDirectionLight>DirectionLightSB:register(t100);
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
	float4 Position : SV_Position;			//���_���W�B
	float3 Normal   : NORMAL;				//�@���B
	float3 Tangent  : TANGENT;				//�ڃx�N�g���B
	float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
	float4 Position : SV_Position;			//���_���W�B
	float3 Normal   : NORMAL;				//�@���B
	float2 TexCoord	: TEXCOORD0;			//UV���W�B
	float3 Tangent	: TANGENT;				//�ڃx�N�g���B
	uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
	float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput {
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float4 posInLVP		: TEXCOORD1;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
	float4 worldPos		: TEXCOORD2;	//���[���h���W�B
};
/*!
 *@brief	�X�L���s����v�Z�B
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


/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�ւ̓��͍\���́B
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//���W�B
};


/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain(VSInputNmTxVcTangent In)
{
	PSInput psInput = (PSInput)0;
	//���[�J�����W�n���烏�[���h���W�n�ɕϊ�����B
	float4 pos = mul(mWorld, In.Position);
	//���[���h���W���s�N�Z���V�F�[�_�[�ɓn���B
	psInput.worldPos = pos;
	//���[���h���W�n����J�������W�n�ɕϊ�����B
	pos = mul(mView, pos);
	//�J�������W�n����X�N���[�����W�n�ɕϊ�����B
	pos = mul(mProj, pos);
	psInput.Position = pos;

	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, psInput.worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/// <summary>
/// �V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin(VSInputNmTxWeights In)
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;

	float w = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
		//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
		//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
		skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}
	//�Ō�̃{�[�����v�Z����B
	skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
	//mul�͏�Z���߁B
	pos = mul(skinning, In.Position);
	psInput.worldPos = pos;
	psInput.Normal = normalize(mul(skinning, In.Normal));
	psInput.Tangent = normalize(mul(skinning, In.Tangent));

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;

	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, psInput.worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	psInput.TexCoord = In.TexCoord;
	return psInput;
}

//�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
//�X�L������
PSInput_ShadowMap VSMainSkin_ShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;

	float w = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
		//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
		//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
		skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}
	//�Ō�̃{�[�����v�Z����B
	skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
	//mul�͏�Z���߁B
	pos = mul(skinning, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// �f�v�X�V���h�E�}�b�v�@���g���āA�e���v�Z����B�B
/// </summary>
//������inout������ƎQ�Ɠn���ɂȂ�B
void CalcShadow(inout float3 lig, float4 posInLvp)
{
	if (isShadowReciever == 1) {	//�V���h�E���V�[�o�[�B
		//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = posInLvp.xy / posInLvp.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {
				//{//�f�o�b�N�R�[�h
				//	lig *= 0.5f;
				//}
			///LVP��Ԃł̐[�x�l���v�Z�B
			float zInLVP = posInLvp.z / posInLvp.w;
			//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
			float zInShadowMap = shadowMap.Sample(Sampler, shadowMapUV);

			if (zInLVP > zInShadowMap + 0.001f) {
				//�e�������Ă���̂ŁA�����キ����
				lig *= 0.5f;
			}
		}
	}
}
void CalcLig(inout float3 lig, float3 normal, float4 pos)
{
	for (int i = 0; i < numDirectionLight; i++) {
		//�g�U�Ɩ��ɂ�郉�C�e�B���O�v�Z
		//*
		float p = dot(normal * -1.0f, DirectionLightSB[i].direction);
		p *= 0.5f;
		p += 0.5f;
		//�v�Z���ʂ��g�D�[���V�F�[�_�[�p�̃e�N�X�`������F���t�F�b�`����
		float4 Col = lightTexture.Sample(Sampler, float2(p, 0.95f));
		//���܂����F����Z����
		lig = Col.xyz * DirectionLightSB[i].color.xyz;
		//*/
	}

}
/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}

//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);

	float3 lig = 0.0f;

	CalcLig(lig, In.Normal, In.Position);

	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//�f�v�X�V���h�E�}�b�v���g���ĉe�𗎂Ƃ��B�B
	CalcShadow(lig, In.posInLVP);

	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}