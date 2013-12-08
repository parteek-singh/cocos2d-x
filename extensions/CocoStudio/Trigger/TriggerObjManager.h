#pragma once
#include "GameSystemExport.h"

#include <vector>
// Direct3D includes
#include <d3d9.h>
#include <d3dx9.h>

class GAMESYSTEM_API COUArchive;

//�������
enum GAMESYSTEM_API TriggerType
{
	TriggerType_Invalid = -1, //��Ч
	TriggerType_Area = 0,     //����      
	TriggerType_Physic,	      //��������
	TriggerType_KeyControl,   //������Ӧ
	TriggerType_Carrier,	  //�ؾ�
	TriggerType_PlayerState,  //��Ҷ���״̬
	TriggerType_Trigger,	  //����������
	TriggerType_Text,         //�ı����
	TriggerType_Weapon,       //�������
	TriggerType_Game,         //��Ϸ���
	TriggerType_Effect,       //��Ч
	TriggerType_Flag,         //����
	TriggerType_Time,         //ʱ��
	TriggerType_Sound,         //��Ч
	TriggerType_Picture,			//ͼƬ
	TriggerType_UI,		//UI����
	TriggerType_Items, //����ˢ�µ�
	TriggerType_CampDeath, //��Ӫ����
	TriggerType_ResetPlayer,//�����������(�¼�)
};

//��������˲������
enum GAMESYSTEM_API TriggerEvent
{
	TriggerEvent_Invalide = -1,
	TriggerEvent_Medical,//����
	TriggerEvent_Ammu,//����
	TriggerEvent_Repair,//ά��
	TriggerEvent_relive,//����
	TriggerEvent_Uav, //UAV
	TriggerEvent_Landmine, //����
	TriggerEvent_Placemine //��װ����
};

struct GAMESYSTEM_API TriggerEventCode
{
	DWORD m_dwAttackerCRID; //�¼��ķ����ߣ���һ������ң�
	DWORD m_dwBeAttackedCRID;//�¼��ĳ����ߣ���һ������ң�
	TriggerEvent m_TriggerEventType;//�¼�����
};

//============����,����,�¼��Ļ���===========
class GAMESYSTEM_API BaseTriggerElement
{
private:
	const TriggerType            m_eType;//����
public:
	BaseTriggerElement( TriggerType type )
		:m_eType(type)
	{

	}

	virtual ~BaseTriggerElement()
	{

	}

	TriggerType GetType() const
	{
		return m_eType;
	}

	// ���ܣ�	���л�������ʵ���������ݵĴ洢���ȡ
	// ������	arc - ָ���������л����ĵ�
	// ע�����������ִ���ʱ�����쳣CSerializerException����������������ú�����Ҫ���д���
	virtual void Serialize(COUArchive& arc) = 0;

	static BaseTriggerElement* QuaryTriggerCodeElement(int codeType);
};
//=============================================

//============һ����������=====================
class GAMESYSTEM_API TriggerElement_Area : public BaseTriggerElement
{
public:
	enum ElementState_Area
	{
		ElementState_Area_Inside = 0,
		ElementState_Area_Outside,
	};

	ElementState_Area m_eState;

	TriggerElement_Area()
		:BaseTriggerElement(TriggerType_Area)
		,m_eState(ElementState_Area_Inside)
	{
	}

	virtual ~TriggerElement_Area()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Physic : public BaseTriggerElement
{
public:
	enum ElementState_Physic
	{
		ElementState_Physic_Die = 0,
		ElementState_Physic_Alive = 1,
	};

	DWORD               m_TargetID;//,Ŀ��ID
	ElementState_Physic m_eState;

	TriggerElement_Physic()
		:BaseTriggerElement( TriggerType_Physic )
		,m_TargetID(-1)
		,m_eState(ElementState_Physic_Die)
	{
	}

	virtual ~TriggerElement_Physic()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_CampDeath : public BaseTriggerElement
{
public:
	enum ElementState_Category
	{
		ElementState_Category_Player = 0,     //���
		ElementState_Category_Prop,              //����
	};

	//������Ӫ
	enum ElementState_Camp
	{
		ElementState_Camp_Blue = 0,
		ElementState_Camp_Red,
		ElementState_Camp_Normal,
	};

	ElementState_Category    m_eCategory;    //����
	ElementState_Camp         m_eCamp;          //��Ӫ
	DWORD                             m_dwKillNum;          //��������

	TriggerElement_CampDeath()
		:BaseTriggerElement(TriggerType_CampDeath)
		,m_eCategory(ElementState_Category_Player)
		,m_eCamp(ElementState_Camp_Normal)
		,m_dwKillNum(-1)
	{}

	virtual ~TriggerElement_CampDeath()
	{}

	virtual void Serialize(COUArchive& arc);
};


class GAMESYSTEM_API TriggerElement_KeyControl : public BaseTriggerElement
{
public:
	enum ElementState_KeyControl
	{
		ElementState_KeyControl_Click = 0,
		ElementState_KeyControl_Up,
		ElementState_KeyControl_Down ,
	};

	ElementState_KeyControl m_eState;
	DWORD                   m_dwKeyId;//��ֵ
	float                   m_fPressedTime;//����ʱ��--ֻ�е�ElementState_KeyControl_Downʱ����Ч

	TriggerElement_KeyControl()
		:BaseTriggerElement(TriggerType_KeyControl)
		,m_eState(ElementState_KeyControl_Click)
		,m_dwKeyId(0)
		,m_fPressedTime(0.0f)
	{
	}

	virtual ~TriggerElement_KeyControl()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Carrier : public BaseTriggerElement
{
public:
	enum ElementState_Carrier
	{
		ElementState_Carrier_TakeOn = 0,
		ElementState_Carrier_Leave,
	};

	ElementState_Carrier m_eState;

	TriggerElement_Carrier()
		:BaseTriggerElement(TriggerType_Carrier)
		,m_eState(ElementState_Carrier_TakeOn)
	{
	}

	virtual ~TriggerElement_Carrier()
	{

	}


	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_PlayerState : public BaseTriggerElement
{
public:
	enum ElementState_PlayerState
	{
		ElementState_PlayerState_Whatever= 0 ,//����
		ElementState_PlayerState_Crouch,
		ElementState_PlayerState_Prone,
		ElementState_PlayerState_Dead,
		ElementState_PlayerState_Stand,
		ElementState_PlayerState_Alive,
	};

	enum ElementState_PlayerEvent
	{
		ElementState_PlayerEvent_Invalide = 0,
		ElementState_PlayerEvent_Repair,
		ElementState_PlayerEvent_Medical,
		ElementState_PlayerEvent_Ammu,
		ElementState_PlayerEvent_relive,
		ElementState_PlayerEvent_Uav,
		ElementState_PlayerEvent_LandMine,
		ElementState_PlayerEvent_Placemine,
	};

	ElementState_PlayerState m_eState;
	ElementState_PlayerEvent m_eEvent;
	ENUM_TEAM_COLOR          m_eTeamColor;
	ENUM_KIT_CLASS				  m_eKitClass;

	TriggerElement_PlayerState()
		:BaseTriggerElement(TriggerType_PlayerState)
		,m_eState(ElementState_PlayerState_Whatever)
		,m_eTeamColor( TEAM_COLOR_NORMAL )
		,m_eKitClass(KIT_CLASS_NUM)
		,m_eEvent(ElementState_PlayerEvent_Invalide)
	{
	}

	virtual ~TriggerElement_PlayerState()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Trigger : public BaseTriggerElement
{
public:
	enum ElementState_Trigger
	{
		ElementState_Trigger_Wake,
		ElementState_Trigger_Sleep,
	};

	ElementState_Trigger m_eState;
	DWORD                m_TargerId;

	TriggerElement_Trigger()
		:BaseTriggerElement(TriggerType_Trigger)
		,m_eState(ElementState_Trigger_Wake)
		,m_TargerId(-1)
	{
	}

	virtual ~TriggerElement_Trigger()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Text : public BaseTriggerElement
{
public:
	DWORD      m_dwTextID; 

	TriggerElement_Text()
		:BaseTriggerElement(TriggerType_Text)
		,m_dwTextID(-1)
	{
	}

	virtual ~TriggerElement_Text()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Weapon : public BaseTriggerElement
{
public:
	enum ElementState_Weapon
	{
		ElementState_Weapon_Enable,//����
		ElementState_Weapon_Destroy,//����
		ElementState_Weapon_Change,//����
	};

	ElementState_Weapon m_eState;
	int	                m_WeaponPos;

	TriggerElement_Weapon()
		:BaseTriggerElement(TriggerType_Weapon)
		,m_eState(ElementState_Weapon_Enable)
		,m_WeaponPos(0)
	{
	}

	virtual ~TriggerElement_Weapon()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Game : public BaseTriggerElement
{
public:
	enum ElementState_Game
	{
		ElementState_Game_Win = 0,//ʤ��
		ElementState_Game_Lost = 1,//ʧ��
		ElementState_Game_Start = 2,//��ʼ
		ElementState_Game_Pause = 3,//��ͣ
	};

	ElementState_Game m_eState;

	TriggerElement_Game()
		:BaseTriggerElement(TriggerType_Game)
		,m_eState(ElementState_Game_Win)
	{
	}

	virtual ~TriggerElement_Game()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Effect : public BaseTriggerElement
{
public:
	enum ElementState_Effect
	{
		ElementState_Effect_Stop = 0,//ֹͣ
		ElementState_Effect_Play,//����
	};

	ElementState_Effect m_eState;
	DWORD m_dwEffectID;
	TriggerElement_Effect()
		:BaseTriggerElement(TriggerType_Effect)
		,m_eState(ElementState_Effect_Stop)
		,m_dwEffectID(-1)
	{
	}

	virtual ~TriggerElement_Effect()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Flag : public BaseTriggerElement
{
public:
	enum ElementState_Flag
	{
		ElementState_Flag_RedColor = 0,
		ElementState_Flag_BuleColor,
		ElementState_Flag_CurRelive,
		ElementState_Flag_Middle,
	};

	ElementState_Flag       m_eState;
	DWORD                   m_dwFlagID;

	TriggerElement_Flag()
		:BaseTriggerElement(TriggerType_Flag)
		,m_eState(ElementState_Flag_RedColor)
		,m_dwFlagID(-1)
	{
	}

	virtual ~TriggerElement_Flag()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Time : public BaseTriggerElement
{
public:
	enum ElementState_Time
	{
		ElementState_Time_Greater = 0,
		ElementState_Time_Less,
	};

	ElementState_Time       m_eState;
	FLOAT                   m_fTimeLimit;
	FLOAT                   m_fCurPassTime;
	TriggerElement_Time()
		:BaseTriggerElement(TriggerType_Time)
		,m_eState(ElementState_Time_Greater)
		,m_fTimeLimit(0.0f)
		,m_fCurPassTime(0.0f)
	{
	}

	virtual ~TriggerElement_Time()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_Sound : public BaseTriggerElement
{
public:
	enum ElementState_Sound
	{
		ElementState_Sound_Wake,
		ElementState_Sound_Sleep,
	};

	ElementState_Sound m_eState;
	DWORD                m_TargerId;

	TriggerElement_Sound()
		:BaseTriggerElement(TriggerType_Sound)
		,m_eState(ElementState_Sound_Wake)
		,m_TargerId(-1)
	{
	}

	virtual ~TriggerElement_Sound()
	{

	}

	virtual void Serialize(COUArchive& arc);
};


class GAMESYSTEM_API TriggerElement_Picture : public BaseTriggerElement
{
public:
	enum ElementState_Picture
	{
		ElementState_Sound_FullScreen,//ȫ��
		ElementState_Sound_Middle,//����
		ElementState_Sound_Rate,//�ȱ���
	};

	DWORD      m_dwPicID; 
	ElementState_Picture m_ePos;

	TriggerElement_Picture()
		:BaseTriggerElement(TriggerType_Picture)
		,m_dwPicID(-1)
		,m_ePos(ElementState_Sound_FullScreen)
	{
	}

	virtual ~TriggerElement_Picture()
	{

	}

	virtual void Serialize(COUArchive& arc);
};


class GAMESYSTEM_API TriggerElement_UI : public BaseTriggerElement
{
public:
	enum ElementState_UI
	{
		ElementState_UI_Introduce = 0,//UI����ؼ���Ľ���
		ElementState_UI_EnemyAndFriend,//���ѽ���
		ElementState_UI_ChoiceSoldierAdd,//����ѡ����渽������
		ElementState_UI_Boss,                   //Boss���ֵĽ���
		ElementState_UI_Normal,                //ͨ�õĽ���
	};

	ElementState_UI      m_eUIIndex; 
	BOOL					   m_bShow;
	DWORD                m_dwTextID;
	DWORD                m_dwCurPartyScore;    //��ǰ����ֵ

	TriggerElement_UI()
		:BaseTriggerElement(TriggerType_UI)
		,m_eUIIndex(ElementState_UI_Introduce)
		,m_bShow(TRUE)
		,m_dwTextID(UINT_MAX)
		,m_dwCurPartyScore(UINT_MAX)
	{
	}

	virtual ~TriggerElement_UI()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

//����ˢ�µ�
class GAMESYSTEM_API TriggerElement_Items : public BaseTriggerElement
{
public:
	//enum ElementState_Items
	//{
	//	ElementState_UI_Introduce = 0,//UI����ؼ���Ľ���
	//	ElementState_UI_EnemyAndFriend,//���ѽ���
	//	ElementState_UI_ChoiceSoldierAdd,//����ѡ����渽������
	//};

	RebuildTriggerState       m_eItemsState;
	DWORD					m_dwItemID;

	TriggerElement_Items()
		:BaseTriggerElement(TriggerType_Items)
		,m_eItemsState(RebuildTriggerState_Unknow)
		,m_dwItemID(-1)
	{
	}

	virtual ~TriggerElement_Items()
	{

	}

	virtual void Serialize(COUArchive& arc);
};

class GAMESYSTEM_API TriggerElement_ResetPlayer : public BaseTriggerElement
{
public:
	BOOL             m_bResetLives;    //�Ƿ���������
	BOOL             m_bResetPos;      //�Ƿ�����λ��
	BOOL             m_bBoutEnd;        //�Ƿ񲨴ν���
	BOOL             m_bBossDying;     //Boss������־
	BOOL             m_bAIRunning;     //����AI�Ƿ��������ģʽ

	TriggerElement_ResetPlayer()
		:BaseTriggerElement(TriggerType_ResetPlayer)
		,m_bResetLives(FALSE)
		,m_bResetPos(FALSE)
		,m_bBoutEnd(FALSE)
		,m_bBossDying(FALSE)
		,m_bAIRunning(FALSE)
	{

	}

	virtual ~TriggerElement_ResetPlayer(){}

	virtual void Serialize(COUArchive& arc);
};
//=============================================

enum TriggerCodeState
{
	TriggerCodeState_Sleep,   //���ߵ�
	TriggerCodeState_Prepare, //������
	TriggerCodeState_Active,  //�����
};

class CTexture;
class GAMESYSTEM_API TriggerCode
{
	enum Type_AutoReliveState
	{
		Type_AutoReliveState_None = 0,
		Type_AutoReliveState_Sleep = 1,
		Type_AutoReliveState_Prepare = 2,
	};
private:
	TriggerCodeState                    m_eState;         //����
	Type_AutoReliveState                m_AutoReliveState;//�������Զ��ָ�״̬(�����TRUE,�����һֱ���ּ���״̬,�����ڲ���������ʱ�Զ�����)
	D3DXVECTOR3							m_vBoundBoxMin;	  //������BoundBoxMin
	D3DXVECTOR3							m_vBoundBoxMax;	  //������BoundBoxMax
	D3DXMATRIX			                m_matWorldInverse;//�������������
	DWORD								m_dwID;           //ID
	////[2011-7-11][֣����][�ô������Ƿ��ɷ���ͬ��]
	////[�ɷ���ͬ���Ĵ�����ֻ���ɷ�������]
	//BOOL                                   m_bHostSync;
	DWORD								m_dwTextID;       //�ı�ID
	DWORD								m_dwSoundID;       //��ЧID
	DWORD								m_dwAideoID;       //��ƵID
	DWORD								m_dwPicID;			//ͼƬID
	TriggerElement_Picture::ElementState_Picture		m_ePicturePos;		//ͼƬ�ڷŷ�ʽ

	std::vector<BaseTriggerElement*>    m_ConditionVec;   //��������
	std::vector<BaseTriggerElement*>    m_TriggerVec;     //��������
	std::vector<BaseTriggerElement*>    m_OccurrenceVec;  //�¼�����


	BOOL                                m_bChackConditionEnable;//�����ж����
	BOOL                                m_bChackTriggerEnable;//�¼��ж����
	CTexture*							 m_pTexture;//��Ⱦ��ͼƬ

	//���һ�����ǲ����������Χ��֮��
	BOOL TestIntersect(const D3DXVECTOR3& pos,BOOL yEnable = TRUE);

	// ���Ԫ��
	BOOL OnChackElement_Area( const BaseTriggerElement* element );
	BOOL OnChackElement_Physic( const BaseTriggerElement* element );
	BOOL OnChackElement_Carrier( const BaseTriggerElement* element );
	BOOL OnChackElement_KeyControl( const BaseTriggerElement* element );
	BOOL OnChackElement_PlayerState( const BaseTriggerElement* element );
	BOOL OnChackElement_Trigger( const BaseTriggerElement* element );
	BOOL OnChackElement_Weapon( const BaseTriggerElement* element );
	BOOL OnChackElement_Flag( const BaseTriggerElement* element );
	BOOL OnChackElement_Game( const BaseTriggerElement* element );
	BOOL OnChackElement_Time( BaseTriggerElement* element ,FLOAT fElapsedTime);
	BOOL OnChackElement_Items( const BaseTriggerElement* element );
	BOOL OnChackElement_CampDeath(const BaseTriggerElement* element);
	// �¼�����
	void OnDealElement_Trigger( const BaseTriggerElement* element );
	void OnDealElement_Physic( const BaseTriggerElement* element );
	void OnDealElement_Text( const BaseTriggerElement* element );
	void OnDealElement_Weapon( const BaseTriggerElement* element );
	void OnDealElement_Game( const BaseTriggerElement* element );
	void OnDealElement_Effect( const BaseTriggerElement* element );
	void OnDealElement_Flag( const BaseTriggerElement* element );
	void OnDealElement_Sound( const BaseTriggerElement* element );
	void OnDealElement_Picture( const BaseTriggerElement* element );
	void OnDealElement_Player( const BaseTriggerElement* element );
	void OnDealElement_UI( const BaseTriggerElement* element );
	void OnDealElement_ResetPlayer(const BaseTriggerElement* element);
	void OnDealElement_CampDeath(const BaseTriggerElement* element);

	//�ѵر�ļ�ֵת���ɵ�ǰ��Ϸ�ļ�ֵ(��������)--�ڶ�ȡ֮�����
	void ChackGameCtrl( DWORD keyId , int& gameKeyId01, int& gameKeyId02 );

	// �������
	BOOL OnChackCondition( FLOAT fElapsedTime );

	// ��ⴥ��
	BOOL OnChackTrigger();

	// �����¼�
	void OnDoOccurrence();
public:
	TriggerCode()
		:m_dwID(-1)
		/*,m_bHostSync(FALSE)*/
		,m_dwTextID(0)//ʹ��O��Ϊ��Чֵ
		,m_dwSoundID(-1)      //��ЧID
	    ,m_dwAideoID(-1)       //��ƵID
		,m_eState(TriggerCodeState_Sleep)
		,m_AutoReliveState(Type_AutoReliveState_None)
		,m_vBoundBoxMin(0.0f,0.0f,0.0f)
		,m_vBoundBoxMax(0.0f,0.0f,0.0f)
		,m_bChackConditionEnable(FALSE)
		,m_bChackTriggerEnable(FALSE)
		,m_dwPicID(-1)
		,m_pTexture(NULL)
		,m_ePicturePos(TriggerElement_Picture::ElementState_Sound_FullScreen)
	{
		m_ConditionVec.clear();
		m_TriggerVec.clear();
		m_OccurrenceVec.clear();
		D3DXMatrixIdentity( &m_matWorldInverse );
	}

	virtual ~TriggerCode()
	{
		Release();
	}

	void Release();

	DWORD GetID()
	{
		return m_dwID;
	}

	TriggerCodeState GetState()
	{
		return m_eState;
	}

	void SetState(TriggerCodeState state);

	void Serialize(COUArchiveEx& arc , BYTE bVersion);

	void Simulate(FLOAT fElapsedTime);

	void Render(LPGFX3D_DIRECT3DDEVICE pDevice);
};


class GAMESYSTEM_API TriggerMng :public CSingleton< TriggerMng >
{
private:
	typedef std::vector<TriggerCode*> TriggerCodeArray;
	TriggerCodeArray		          m_TriggerCodeArray; //����������Ϣ����
	std::vector<TriggerCodeState> m_TriggerStateVec;

	std::vector<TriggerEventCode>		m_TriggerEventArray; //���津������˲����������
public:
	TriggerMng();
	~TriggerMng();
	// ���ܣ�	���л�������ʵ���������ݵĴ洢���ȡ
	// ������	arc - ָ���������л����ĵ�
	// ע�����������ִ���ʱ�����쳣CSerializerException����������������ú�����Ҫ���д���
	void Serialize(COUArchiveEx& arc);

	//���ܣ�ɾ��ָ���ͷ���Դ
	void Release();

	// ֡
	void Simulate(FLOAT fElapsedTime);

	// ��Ⱦ
	void Render(LPGFX3D_DIRECT3DDEVICE pDevice);

	//[2011-2-10][֣����][��ú�����m_TriggerCodeArray������]
	TriggerCodeArray GetTriggerCodeArray()
	{
		return m_TriggerCodeArray;
	}

	void SetTriggerCodeArray(TriggerCodeArray tmp_triggerCodeArray)
	{
		m_TriggerCodeArray = tmp_triggerCodeArray;
	}

	void SetTriggerState(std::vector<TriggerCodeState> tmpTriggerState);


	// ���Ҵ�����
	TriggerCode* FindTrigger(DWORD id);

	//����˲������������
	void AddTriggerEvent(TriggerEventCode& triggerEvent);

	//�����Ƿ��й̶����͵�����¼�
	BOOL IfHappenTriggerEvent(TriggerEvent eTriggerEvent);
};

//ȡ��ȫ�ֵĴ�����������
inline TriggerMng* GetTriggerManager()
{
	return TriggerMng::GetSingletonPtr();
}
