/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
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
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float4 posInLVP		: TEXCOORD1;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
	float3 worldPos	: TEXCOORD2;	//���[���h���W�B
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
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//���[�J�����W�n���烏�[���h���W�n�ɕϊ�����B
	float4 pos = mul(mWorld, In.Position);
	//���[���h���W���s�N�Z���V�F�[�_�[�ɓn���B
	psInput.worldPos = pos.xyz;
	//���[���h���W�n����J�������W�n�ɕϊ�����B
	pos = mul(mView, pos);
	//�J�������W�n����X�N���[�����W�n�ɕϊ�����B
	pos = mul(mProj, pos);
	psInput.Position = pos;

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
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
/// ���C���o�[�g�g�U���˂��v�Z����B
/// </summary>
float3 CalcDiffuseLight(float3 normal)
{
	float3 lig = 0.0f;
	//numDirectionLightv�̒l�����Ă��Ȃ��B
	//for (int i = 0; i < numDirectionLight; i++) {
	//�Ƃ肠�����B��{�œ��ĂĂ�B
	for (int i = 0; i < numDirectionLight; i++) {
		//�����o�[�g�g�U���ˁB
		lig += max(0.5f, dot(normal * -1.0f, DirectionLightSB[i].direction)) * DirectionLightSB[i].color;
	}
	return lig;
}
float3 Toon(float3 normal)
{

}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);


	float3 lig = 0.0f;
	//���C���o�[�g�g�U����
	//lig += CalcDiffuseLight(In.Normal);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	//finalColor.xyz = albedoColor.xyz * lig;

	{
		for (int i = 0; i < numDirectionLight; i++) {
			//2�K���̉A�e�����߂�B
			//���C�g�̕����Ɩ@���̓��ς����ƃ��C�g�̋��������܂�B
			//���������l�ȉ�(�����0.2)�Ȃ�Â��e�N�X�`�����g���B
			//����ȏ�Ȃ疾�邢�e�N�X�`�����g���B
			float3 color = 0.0f;
			if (dot(-DirectionLightSB[i].direction, In.Normal) < 0.1f) {
				color = albedoColor.xyz * 0.5f;
			}
			else {
				color = albedoColor.xyz * 1.0f;
			}
			//�����𓖂Ă�B
			float3 eyeDir = normalize(eyepos - In.worldPos);
			float lim = (1.0f - dot(-In.Normal, eyeDir)) * 1.0f;								//�J�����̕����Ɛ����ȏꍇ�t���̋����������Ȃ�B
			lim *= max(0.0f, dot(eyeDir, -DirectionLightSB[i].direction));						//���S�ɋt�s���Ă�����baseLim�̒l�����̂܂܂ł�B
			if (lim > 0.85f) {
				//�t�����������Ă���B
				color = albedoColor.xyz;
			}
			finalColor = float4(color.xyz, 1.0f);
		}
	}

	return finalColor;
}