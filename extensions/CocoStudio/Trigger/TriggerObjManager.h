#pragma once
#include "GameSystemExport.h"

#include <vector>
// Direct3D includes
#include <d3d9.h>
#include <d3dx9.h>

class GAMESYSTEM_API COUArchive;

//结点类型
enum GAMESYSTEM_API TriggerType
{
	TriggerType_Invalid = -1, //无效
	TriggerType_Area = 0,     //区域      
	TriggerType_Physic,	      //物理物体
	TriggerType_KeyControl,   //按键相应
	TriggerType_Carrier,	  //载具
	TriggerType_PlayerState,  //玩家动作状态
	TriggerType_Trigger,	  //触发器处理
	TriggerType_Text,         //文本变更
	TriggerType_Weapon,       //武器变更
	TriggerType_Game,         //游戏变更
	TriggerType_Effect,       //特效
	TriggerType_Flag,         //旗帜
	TriggerType_Time,         //时间
	TriggerType_Sound,         //音效
	TriggerType_Picture,			//图片
	TriggerType_UI,		//UI界面
	TriggerType_Items, //道具刷新点
	TriggerType_CampDeath, //阵营死亡
	TriggerType_ResetPlayer,//重置玩家属性(事件)
};

//触发器的瞬发条件
enum GAMESYSTEM_API TriggerEvent
{
	TriggerEvent_Invalide = -1,
	TriggerEvent_Medical,//治疗
	TriggerEvent_Ammu,//补给
	TriggerEvent_Repair,//维修
	TriggerEvent_relive,//急救
	TriggerEvent_Uav, //UAV
	TriggerEvent_Landmine, //地雷
	TriggerEvent_Placemine //安装地雷
};

struct GAMESYSTEM_API TriggerEventCode
{
	DWORD m_dwAttackerCRID; //事件的发起者（不一定是玩家）
	DWORD m_dwBeAttackedCRID;//事件的承受者（不一定是玩家）
	TriggerEvent m_TriggerEventType;//事件类型
};

//============条件,触发,事件的基类===========
class GAMESYSTEM_API BaseTriggerElement
{
private:
	const TriggerType            m_eType;//类型
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

	// 功能：	序列化函数，实现数据内容的存储与读取
	// 参数：	arc - 指定用于序列化的文档
	// 注：本函数出现错误时会抛异常CSerializerException出来，所以外面调用函数需要进行处理
	virtual void Serialize(COUArchive& arc) = 0;

	static BaseTriggerElement* QuaryTriggerCodeElement(int codeType);
};
//=============================================

//============一大陀派生类=====================
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

	DWORD               m_TargetID;//,目标ID
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
		ElementState_Category_Player = 0,     //玩家
		ElementState_Category_Prop,              //道具
	};

	//所属阵营
	enum ElementState_Camp
	{
		ElementState_Camp_Blue = 0,
		ElementState_Camp_Red,
		ElementState_Camp_Normal,
	};

	ElementState_Category    m_eCategory;    //种类
	ElementState_Camp         m_eCamp;          //阵营
	DWORD                             m_dwKillNum;          //死亡个数

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
	DWORD                   m_dwKeyId;//键值
	float                   m_fPressedTime;//持续时间--只有当ElementState_KeyControl_Down时才有效

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
		ElementState_PlayerState_Whatever= 0 ,//任意
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
		ElementState_Weapon_Enable,//存在
		ElementState_Weapon_Destroy,//销毁
		ElementState_Weapon_Change,//更换
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
		ElementState_Game_Win = 0,//胜利
		ElementState_Game_Lost = 1,//失败
		ElementState_Game_Start = 2,//开始
		ElementState_Game_Pause = 3,//暂停
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
		ElementState_Effect_Stop = 0,//停止
		ElementState_Effect_Play,//播放
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
		ElementState_Sound_FullScreen,//全屏
		ElementState_Sound_Middle,//居中
		ElementState_Sound_Rate,//等比率
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
		ElementState_UI_Introduce = 0,//UI界面关键点的介绍
		ElementState_UI_EnemyAndFriend,//敌友界面
		ElementState_UI_ChoiceSoldierAdd,//兵种选择界面附属界面
		ElementState_UI_Boss,                   //Boss出现的界面
		ElementState_UI_Normal,                //通用的界面
	};

	ElementState_UI      m_eUIIndex; 
	BOOL					   m_bShow;
	DWORD                m_dwTextID;
	DWORD                m_dwCurPartyScore;    //当前兵力值

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

//道具刷新点
class GAMESYSTEM_API TriggerElement_Items : public BaseTriggerElement
{
public:
	//enum ElementState_Items
	//{
	//	ElementState_UI_Introduce = 0,//UI界面关键点的介绍
	//	ElementState_UI_EnemyAndFriend,//敌友界面
	//	ElementState_UI_ChoiceSoldierAdd,//兵种选择界面附属界面
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
	BOOL             m_bResetLives;    //是否重置命数
	BOOL             m_bResetPos;      //是否重置位置
	BOOL             m_bBoutEnd;        //是否波次结束
	BOOL             m_bBossDying;     //Boss死亡标志
	BOOL             m_bAIRunning;     //所有AI是否进入逃跑模式

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
	TriggerCodeState_Sleep,   //休眠的
	TriggerCodeState_Prepare, //就绪的
	TriggerCodeState_Active,  //激活的
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
	TriggerCodeState                    m_eState;         //激活
	Type_AutoReliveState                m_AutoReliveState;//激活后的自动恢复状态(如果是TRUE,激活后一直保持激活状态,否则在不满足条件时自动休眠)
	D3DXVECTOR3							m_vBoundBoxMin;	  //场景中BoundBoxMin
	D3DXVECTOR3							m_vBoundBoxMax;	  //场景中BoundBoxMax
	D3DXMATRIX			                m_matWorldInverse;//世界矩阵的逆矩阵
	DWORD								m_dwID;           //ID
	////[2011-7-11][郑怡曼][该触发器是否由房主同步]
	////[由房主同步的触发器只能由房主触发]
	//BOOL                                   m_bHostSync;
	DWORD								m_dwTextID;       //文本ID
	DWORD								m_dwSoundID;       //音效ID
	DWORD								m_dwAideoID;       //视频ID
	DWORD								m_dwPicID;			//图片ID
	TriggerElement_Picture::ElementState_Picture		m_ePicturePos;		//图片摆放方式

	std::vector<BaseTriggerElement*>    m_ConditionVec;   //条件数组
	std::vector<BaseTriggerElement*>    m_TriggerVec;     //触发数组
	std::vector<BaseTriggerElement*>    m_OccurrenceVec;  //事件数组


	BOOL                                m_bChackConditionEnable;//条件判定结果
	BOOL                                m_bChackTriggerEnable;//事件判定结果
	CTexture*							 m_pTexture;//渲染的图片

	//检测一个点是不是在这个包围盒之内
	BOOL TestIntersect(const D3DXVECTOR3& pos,BOOL yEnable = TRUE);

	// 检测元素
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
	// 事件操作
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

	//把地编的键值转换成当前游戏的键值(可能有俩)--在读取之后调用
	void ChackGameCtrl( DWORD keyId , int& gameKeyId01, int& gameKeyId02 );

	// 检测条件
	BOOL OnChackCondition( FLOAT fElapsedTime );

	// 检测触发
	BOOL OnChackTrigger();

	// 处理事件
	void OnDoOccurrence();
public:
	TriggerCode()
		:m_dwID(-1)
		/*,m_bHostSync(FALSE)*/
		,m_dwTextID(0)//使用O作为无效值
		,m_dwSoundID(-1)      //音效ID
	    ,m_dwAideoID(-1)       //视频ID
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
	TriggerCodeArray		          m_TriggerCodeArray; //触发器的信息数组
	std::vector<TriggerCodeState> m_TriggerStateVec;

	std::vector<TriggerEventCode>		m_TriggerEventArray; //保存触发器的瞬发条件数组
public:
	TriggerMng();
	~TriggerMng();
	// 功能：	序列化函数，实现数据内容的存储与读取
	// 参数：	arc - 指定用于序列化的文档
	// 注：本函数出现错误时会抛异常CSerializerException出来，所以外面调用函数需要进行处理
	void Serialize(COUArchiveEx& arc);

	//功能：删除指针释放资源
	void Release();

	// 帧
	void Simulate(FLOAT fElapsedTime);

	// 渲染
	void Render(LPGFX3D_DIRECT3DDEVICE pDevice);

	//[2011-2-10][郑怡曼][获得和设置m_TriggerCodeArray的数据]
	TriggerCodeArray GetTriggerCodeArray()
	{
		return m_TriggerCodeArray;
	}

	void SetTriggerCodeArray(TriggerCodeArray tmp_triggerCodeArray)
	{
		m_TriggerCodeArray = tmp_triggerCodeArray;
	}

	void SetTriggerState(std::vector<TriggerCodeState> tmpTriggerState);


	// 查找触发器
	TriggerCode* FindTrigger(DWORD id);

	//加入瞬发条件管理中
	void AddTriggerEvent(TriggerEventCode& triggerEvent);

	//查找是否有固定类型的玩家事件
	BOOL IfHappenTriggerEvent(TriggerEvent eTriggerEvent);
};

//取得全局的触发器管理器
inline TriggerMng* GetTriggerManager()
{
	return TriggerMng::GetSingletonPtr();
}
