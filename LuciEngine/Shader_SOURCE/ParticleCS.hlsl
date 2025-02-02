#include "globals.hlsli"

RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

void InitializeParticle(int id)
{
    ParticleBuffer[id].active = 1;
    ParticleBuffer[id].time = 0;
    ParticleBuffer[id].lifeTime = particleLifetime;
    ParticleBuffer[id].rotation = particleStartRotation;
    
    // 랜덤값으로 위치와 방향을 설정한다.
    // 샘플링을 시도할 UV 를 계산한다.=> 노이즈로부터의 sampling    
    float2 vUV = float2((float) id / elementCount, 0.5f);
    vUV.x += particleElapsedTime;
    vUV.y += sin((vUV.x + particleElapsedTime) * 3.141592f + 2.f * 10.f) * 0.5f;
    
    float randomValue;
    if(id % 2 == 0)
        randomValue = GaussianBlur(vUV).x;
    else
        randomValue = GaussianBlur(vUV).y;
    
    float4 vRandom = float4
            (
                  GaussianBlur(vUV + float2(0.f, 0.f)).x
                , GaussianBlur(vUV + float2(0.1f, 0.f)).x
                , GaussianBlur(vUV + float2(0.2f, 0.f)).x
                , GaussianBlur(vUV + float2(0.3f, 0.f)).x
            );

// Calculate a random float within the range [a, b]
    float randomAngle = particleAngle1 + randomValue * (particleAngle2 - particleAngle1);
    float3 direction = float3(cos(randomAngle), sin(randomAngle), 0);
    direction = normalize(mul(WorldMatrix, float4(direction, 0.0))).xyz;
    direction = normalize(direction);
    ParticleBuffer[id].velocity = direction * particleStartSpeed;
    
    float4 position = float4(particleOffset, 1);
    position += float4(particleStartRadius * direction, 0);
    position.xyz = vRandom.xyz * 2.0f;
    position.x -= 0.65f;
    position.y -= 1.4f;
    position.z = 0.0f;
    position = mul(position, WorldMatrix);
    ParticleBuffer[id].position = position; //mul(float4(particleOffset, 1), WorldMatrix);

}

void UpdateParticle(int id)
{
    
    float t = ParticleBuffer[id].time / ParticleBuffer[id].lifeTime;
    if (t >= 1.0f)
        ParticleBuffer[id].active = 0;
    else
    {
        ParticleBuffer[id].time += particleDeltaTime;
        float3 acceleration = float3(0, -particleGravityRate, 0);
            
        ParticleBuffer[id].position += ParticleBuffer[id].velocity *
            particleDeltaTime + 0.5 * acceleration * particleDeltaTime * particleDeltaTime;
            
        ParticleBuffer[id].rotation += particleRotationSpeed * particleDeltaTime;
        ParticleBuffer[id].velocity += acceleration * particleDeltaTime;
    }
}

[numthreads(128, 1, 1)]// run with 128 thread each dimension
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint id = DTid.x;
    //thread termination check => 할당되지 않은 element는 작동하지 않는다.
    if (elementCount <= id)
		return;

    //if particle is not active
    if (ParticleBuffer[id].active == 0)
    {
        //if there are active particles to process
        while (ParticleSharedBuffer[0].ActiveSharedCount > 0)
        {
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1;// <- process one particle at one time
            
            // 쓰레드 동기화 Interlock 관련 함수            
            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , origin, exchange, exchange);//activeSharedCount을 origin에서 exchange로 바꾸기 시도.
            
            if (origin == exchange) // activeSharedCount update을 성공했다면 particle initialize
            {
                InitializeParticle(id);
                break;
            }
        }
    }
    else
    {
        UpdateParticle(id);        
    }
}

