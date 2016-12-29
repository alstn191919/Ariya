//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// ApplyShadowShader
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// ApplyShadowTorus
//--------------------------------------------------------------//
string ApplyShadowShader_ApplyShadowTorus_Torus : ModelData = "..\\..\\..\\..\\ptT\\10_ShadowMapping\\Torus.x";

float4x4 gWorldMatrix : World;
float4x4 gLightViewMatrix
<
   string UIName = "gLightViewMatrix";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
> = float4x4( 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00 );
float4x4 gLightProjectionMatrix : Projection;

float4 gWorldLightPosition
<
   string UIName = "gWorldLightPosition";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 500.00, 500.00, -500.00, 1.00 );
float4 gWorldCameraPosition : ViewPosition;

float4x4 gViewProjectionMatrix : ViewProjection;

struct VS_INPUT 
{
   float4 mPosition: POSITION;
   float3 mNormal: NORMAL;
   float3 mTangent: TANGENT;
   float3 mBinormal: BINORMAL;
   float2 mUV: TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition: POSITION;
   float4 mClipPosition: TEXCOORD1;
   float mDiffuse: TEXCOORD2;
   
   float2 mUV: TEXCOORD3;
   float3 mLightDir : TEXCOORD4;
   float3 mViewDir: TEXCOORD5;
   float3 T : TEXCOORD6;
   float3 B : TEXCOORD7;
   float3 N : TEXCOORD8;
   float3 mDisVec : TEXCOORD9;
};


VS_OUTPUT ApplyShadowShader_ApplyShadowTorus_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
  
   float4x4 lightViewMatrix = gLightViewMatrix;

   float4 worldPosition = mul(Input.mPosition, gWorldMatrix);
   Output.mPosition = mul(worldPosition, gViewProjectionMatrix);

   Output.mClipPosition = mul(worldPosition, lightViewMatrix);
   Output.mClipPosition = mul(Output.mClipPosition, gLightProjectionMatrix);
   
   float3 lightDir = normalize(worldPosition.xyz - gWorldLightPosition.xyz);
   float3 worldNormal = normalize(mul(Input.mNormal, (float3x3)gWorldMatrix));
   Output.mDiffuse = dot(-lightDir, worldNormal);
   
   Output.mUV = Input.mUV;

   Output.mLightDir = normalize(lightDir);
   
   Output.mDisVec.xyz = Input.mPosition.xyz - gWorldLightPosition.xyz;
   
   float3 viewDir = normalize(worldPosition.xyz - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir;
   
   Output.N = worldNormal;
   
   float3 worldTangent = mul(Input.mTangent, (float3x3)gWorldMatrix );
   Output.T = normalize(worldTangent);
   
   float3 worldBinormal = mul(Input.mBinormal, (float3x3)gWorldMatrix );
   Output.B = normalize(worldBinormal);


   return Output;
}
texture ShadowMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\ptT\\10_ShadowMapping\\";
>;
sampler2D ShadowSampler = sampler_state
{
   Texture = (ShadowMap_Tex);
};
texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\ptT\\10_ShadowMapping\\Fieldstone_DM.tga";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};
texture SpecularMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\ptT\\10_ShadowMapping\\fieldstone_SM.tga";
>;
sampler2D SpecularSampler = sampler_state
{
   Texture = (SpecularMap_Tex);
};
texture NormalMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\ptT\\10_ShadowMapping\\fieldstone_NM.tga";
>;
sampler2D NormalSampler = sampler_state
{
   Texture = (NormalMap_Tex);
};

float4 gObjectColor
<
   string UIName = "gObjectColor";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 1.00, 1.00, 1.00, 1.00 );
float3 gLightColor
<
   string UIName = "gLightColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 1.00, 1.00, 1.00 );
float gRange
<
   string UIName = "gRange";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 6000.00 );
float gAlphaBlend
<
   string UIName = "gAlphaBlend";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 0.80 );


struct PS_INPUT
{
   float4 mClipPosition: TEXCOORD1;
   float mDiffuse: TEXCOORD2;
   
   float2 mUV : TEXCOORD3;
   float3 mLightDir : TEXCOORD4;
   float3 mViewDir: TEXCOORD5;
   float3 T : TEXCOORD6;
   float3 B : TEXCOORD7;
   float3 N : TEXCOORD8;
   float3 mDisVec : TEXCOORD9;
};

float4 ApplyShadowShader_ApplyShadowTorus_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
   float3 rgb = saturate(Input.mDiffuse) * gObjectColor ;
   
   float currentDepth = Input.mClipPosition.z / Input.mClipPosition.w;
   
   float2 uv = Input.mClipPosition.xy / Input.mClipPosition.w;
   
   uv.y = -uv.y;
   uv = uv * 0.5 + 0.5;
   uv.x = saturate(uv.x);
   uv.y = saturate(uv.y);
   float shadowDepth = tex2D(ShadowSampler, uv).r;
  
   //if (currentDepth > shadowDepth + 0.0100125f && uv.x < 1 && uv.y < 1 && uv.x >= 0 && uv.y >= 0)
   if ((currentDepth > shadowDepth + 0.0100125f) && uv.x < 1 && uv.y < 1 && uv.x >= 0 && uv.y >= 0)
   {
      rgb *= 0.2f;
   }
   
   //return( float4( rgb, 1.0f ) );
   
    float3 tangentNormal = tex2D(NormalSampler, Input.mUV).xyz;
   tangentNormal = normalize(tangentNormal * 2 - 1);
   
   float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
   TBN = transpose(TBN);
   float3 worldNormal = mul(TBN, tangentNormal);
   
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   float3 lightDir = normalize(Input.mLightDir);
   float3 diffuse = saturate(dot(worldNormal, -lightDir));   
   diffuse = albedo.rgb * diffuse;
   
   float3 specular = 0;
   if ( diffuse.x > 0 )
   {
      float3 reflection = reflect(lightDir, worldNormal);
      float3 viewDir = normalize(Input.mViewDir); 

      specular = saturate(dot(reflection, -viewDir ));
      specular = pow(specular, 25.0f);
      
      float4 specularIntensity  = tex2D(SpecularSampler, Input.mUV);
		  specular *= specularIntensity.rgb ;
   }

   float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo;
      
   float Power = (gRange - length(Input.mDisVec)) / gRange;
   return float4((ambient + diffuse + specular)*Power*gAlphaBlend * rgb, 1);
}

//--------------------------------------------------------------//
// Technique Section for ApplyShadowShader
//--------------------------------------------------------------//
technique ApplyShadowShader
{
   pass ApplyShadowTorus
   {
      VertexShader = compile vs_3_0 ApplyShadowShader_ApplyShadowTorus_Vertex_Shader_vs_main();
      PixelShader = compile ps_3_0 ApplyShadowShader_ApplyShadowTorus_Pixel_Shader_ps_main();
   }

}

