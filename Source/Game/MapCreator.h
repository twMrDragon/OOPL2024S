#pragma once
#include "MovingObject.h"
#include "Bezier.h"
#include "Enemy.h"
#include "MapData.h"
#include "BulletCreator.h"

class MapCreator
{
public:
	static void init(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);

private:
	// stage 1
	static void initStage1(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	// �Ŧ�p�� ���W�i�� ���|�s��
	static void initStage1Type1Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// �Ŧ�p�� �k�W�i�� ���|�s��
	static void initStage1Type2Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// �Ŧ�p�� �����i�� �@���i����p��
	static void initStage1Type3Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// ����p�� �H�K�i�� �|�o�g�l�u
	static void initStage1Type4Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// �Ŧ�p�� �H�K�i��
	static void initStage1Type5Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// �Ŧ�p�� �@����� �k�W�i�� ���|�s��
	static void initStage1Type6Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// �Ŧ�p�� �@����� ���W�i�� ���|�s��
	static void initStage1Type7Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// TODO:stage 1 �]��
	// �Ĥ@�� boss �Ĥ@���q 
	static void initStage1Boss1(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	// �Ĥ@�� boss �ĤG���q
	static void initStage1Boss2(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);

	// stage 2
	static void initStage2(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	// TODO stage 2 �ĤH �Ѥk����
	// �զ���I ���⭸�� �Ѥk����
	static void initStage2Type1Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// �Ŧ�p�� �������| �ѥ��V�k�J
	static void initStage2Type2Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// �Ŧ�p�� �������| �ѥk�V���J
	static void initStage2Type3Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
};

