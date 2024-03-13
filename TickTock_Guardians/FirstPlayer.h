#pragma once
#include "TickTockScene.h"

class FirstPlayer : public TickTockScene
{
public:
	FirstPlayer(GameObjectManager* gameObjectManager);

	virtual void Enter();
	virtual eSceneState HandleTransition();
	virtual void Update(float deltaTime);
	virtual void Exit();

	void OnFinishTracing(std::any data);
	void OnTransitionNextPlayer(std::any data);
	void SetCharacterIndex(std::any data);
	void OnSkipTracing(std::any data);


private:
	bool mbIsActivated = false;
	uint32_t mCharacterId1 = 0;	// ù ��° ĳ������ ���̵�
	bool mbIsFinished = false;	// ù ��° ĳ������ �������� �����°�
	bool mbIsStart = false;		// ù ��° ĳ���Ͱ� �������°�

	uint32_t mCharacterId2 = 0;	// �� ��° ĳ������ ���̵�

	uint32_t mCharacterId3 = 0;	// �� ��° ĳ������ ���̵�

	uint32_t mDigitCounterColonId = 0;	// ������ ī������ ���̵� (0.01�� �ڸ���)
	uint32_t mDigitCounterId0001 = 0;	// ������ ī������ ���̵� (0.01�� �ڸ���)
	uint32_t mDigitCounterId001 = 0;	// ������ ī������ ���̵� (0.1�� �ڸ���)
	uint32_t mDigitCounterId01 = 0;	// ������ ī������ ���̵� (1�� �ڸ���)
	uint32_t mDigitCounterId10 = 0;	// ������ ī������ ���̵� (10�� �ڸ���)

	uint32_t mPortraitId01 = 0;		// �ʻ�ȭ�� ���̵�
	uint32_t mPortraitId02 = 0;		// �ʻ�ȭ�� ���̵�
	uint32_t mPortraitId03 = 0;		// �ʻ�ȭ�� ���̵�

	bool mbIsResetStage = false;

	//TagType firstType;
	//TagType secondType;
	//TagType thirdType;
};