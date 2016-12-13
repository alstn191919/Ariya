#pragma once
class cParticle
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
public:
	void Setup();
	void Update();
	void Render();
	cParticle();
	~cParticle();
};

