#pragma once

class cFrostumCulling
{
private:
	std::vector<D3DXPLANE> v_Plane;
	SYNTHESIZE(bool, _isUpdate, isUpdate);
public:
	void Setup();
	void Update();
	bool PositionCulling(IN D3DXVECTOR3 _ShpereCenter);
	D3DXVECTOR3 VecInvers(D3DXVECTOR3 _Vec);
	cFrostumCulling();
	~cFrostumCulling();
};

