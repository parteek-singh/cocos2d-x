#pragma once

#include "stdafx.h"
#include "..\include\TriggerObjManager.h"
#include "..\include\ModuleMng.h"
#include "..\include\PlayerManager.h"
#include "..\include\Host.h"
#include "..\include\Scene.h"
#include "..\include\MediaCentral.h"
#include "..\include\CompetitionRulesBase.h"
#include "..\include\PVECompetitionRules.h"
#include "..\include\EffectObj.h"
#include "GmaEffectPlayer.h"
#include "..\include\graphiceffectplayer.h"
#include "..\..\BaseDef\include\UIFont.h"
#include "Tfx2001.h"
#include "..\include\occupy.h"
#include "..\include\OccupyManager.h"
#include "..\..\UISystem\Include\UIDriver_DX8.h"
#include "..\UIInclude\IntroductoryVideoDlg.h"
#include "..\UIInclude\ChoiceSoldiersDlg.h"
#include "..\UIInclude\TrainingUIDlg.h"
#include "..\UIInclude\RaceResultPVE.h"


extern BASEDEF_API DWORD cfg_Game_dwForward;
extern BASEDEF_API DWORD cfg_Game_dwForward02;
extern BASEDEF_API DWORD cfg_Game_dwBackward;
extern BASEDEF_API DWORD cfg_Game_dwBackward02;
extern BASEDEF_API DWORD cfg_Game_dwLeftMove;
extern BASEDEF_API DWORD cfg_Game_dwLeftMove02;
extern BASEDEF_API DWORD cfg_Game_dwRightMove;
extern BASEDEF_API DWORD cfg_Game_dwRightMove02;
extern BASEDEF_API BOOL  cfg_Graphic_bRenderTriggerDebug;

extern BASEDEF_API DWORD cfg_Game_bIsTrainYardID;//射击训练关卡ID
extern BASEDEF_API int cfg_Game_iTriggerTextTop_Low;//训练关卡文本位置，低
extern BASEDEF_API int cfg_Game_iTriggerTextTop_Heigh;//训练关卡文本位置，高
//[2011-04-29][熊嘉琪][英文版提示文本变小]
extern  BASEDEF_API  ENUM_LANGUAGE_TYPE		cfg_Game_eLanguage		;//语种

//====================触发器相关==================

BaseTriggerElement* BaseTriggerElement::QuaryTriggerCodeElement(int codeType)
{
	switch( static_cast<TriggerType>(codeType) )
	{
	case TriggerType_Area:
		{
			TriggerElement_Area* tpCode = new TriggerElement_Area();
			return tpCode;
		}
		break;

	case TriggerType_Physic:
		{
			TriggerElement_Physic* tpCode = new TriggerElement_Physic();
			return tpCode;
		}
		break;

	case TriggerType_KeyControl:
		{
			TriggerElement_KeyControl* tpCode = new TriggerElement_KeyControl();
			return tpCode;
		}
		break;
	case TriggerType_Carrier:
		{
			TriggerElement_Carrier* tpCode = new TriggerElement_Carrier();
			return tpCode;
		}
		break;

	case TriggerType_PlayerState:
		{
			TriggerElement_PlayerState* tpCode = new TriggerElement_PlayerState();
			return tpCode;
		}
		break;

	case TriggerType_Trigger:
		{
			TriggerElement_Trigger* tpCode = new TriggerElement_Trigger();
			return tpCode;
		}
		break;

	case TriggerType_Text:
		{
			TriggerElement_Text* tpCode = new TriggerElement_Text();
			return tpCode;
		}
		break;

	case TriggerType_Weapon:
		{
			TriggerElement_Weapon* tpCode = new TriggerElement_Weapon();
			return tpCode;
		}
		break;

	case TriggerType_Game:
		{
			TriggerElement_Game* tpCode = new TriggerElement_Game();
			return tpCode;
		}
		break;

	case TriggerType_Effect:
		{
			TriggerElement_Effect* tpCode = new TriggerElement_Effect();
			return tpCode;
		}
		break;

	case TriggerType_Flag:
		{
			TriggerElement_Flag* tpCode = new TriggerElement_Flag();
			return tpCode;
		}
		break;

	case TriggerType_Time:
		{
			TriggerElement_Time* tpCode = new TriggerElement_Time();
			return tpCode;
		}
		break;

	case TriggerType_Sound:
		{
			TriggerElement_Sound* tpCode = new TriggerElement_Sound();
			return tpCode;
		}
		break;

	case TriggerType_Picture:
		{
			TriggerElement_Picture* tpCode = new TriggerElement_Picture();
			return tpCode;
		}
		break;
	case TriggerType_UI:
		{
			TriggerElement_UI* tpCode = new TriggerElement_UI();
			return tpCode;
		}
		break;

	case TriggerType_Items:
		{
			TriggerElement_Items* tpCode = new TriggerElement_Items();
			return tpCode;
		}
		break;
		
	case TriggerType_CampDeath:
		{
			TriggerElement_CampDeath* tpCode = new TriggerElement_CampDeath();
			return tpCode;
		}
		break;

	case TriggerType_ResetPlayer:
		{
			TriggerElement_ResetPlayer* tpCode = new TriggerElement_ResetPlayer();
			return tpCode;
		}
		break;

	default:
		ASSERT(FALSE);
		break;
	}

	ASSERT(FALSE);
	return NULL;
}

void TriggerElement_Area::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;

		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Area>(tpState);
	}
}

void TriggerElement_Physic::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_TargetID;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;
		arc >> m_TargetID;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Physic>(tpState);
	}

}

void TriggerElement_CampDeath::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if(arc.IsStoring())
	{
		arc << dwVersion;
		arc << static_cast<int>(m_eCategory);
		arc << static_cast<int>(m_eCamp);
		arc << m_dwKillNum;
	}
	else
	{
		arc >> dwVersion;
		DWORD tmp_Category(0);
		arc >> tmp_Category;
		m_eCategory = static_cast<ElementState_Category>(tmp_Category);
		DWORD tmp_Camp(0);
		arc >> tmp_Camp;
		m_eCamp = static_cast<ElementState_Camp>(tmp_Camp);
		arc >> m_dwKillNum;
	}
}

void TriggerElement_KeyControl::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_dwKeyId;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;
		arc >> m_dwKeyId;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_KeyControl>(tpState);
	}
}

void TriggerElement_Carrier::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;

		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Carrier>(tpState);
	}

}

void TriggerElement_PlayerState::Serialize(COUArchive& arc)
{
	//DWORD dwVersion = 0;
	//DWORD dwVersion = 1;//增加了玩家队伍色判定
	//DWORD dwVersion = 2;//增加了玩家兵种
	DWORD dwVersion = 3;//增加了玩家瞬发事件

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << static_cast<int>( m_eState );
		arc << static_cast<int>( m_eTeamColor );
		arc << static_cast<int>( m_eKitClass);
		arc << static_cast<int>( m_eEvent);
	}
	else
	{
		arc >> dwVersion;

		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_PlayerState>( tpState );
		
		if ( dwVersion >= 1 )
		{
			int tpTeamColor;
			arc >> tpTeamColor;
			m_eTeamColor = static_cast<ENUM_TEAM_COLOR>( tpTeamColor );
		}
		if ( dwVersion >= 2 )
		{
			int tpKit;
			arc >> tpKit;
			m_eKitClass = static_cast<ENUM_KIT_CLASS>( tpKit );
		}
		if ( dwVersion >= 3 )
		{
			int tpEvent;
			arc >> tpEvent;
			m_eEvent = static_cast<ElementState_PlayerEvent>( tpEvent );
		}
	}
}

void TriggerElement_Trigger::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_TargerId;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;
		arc >> m_TargerId;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Trigger>(tpState);
	}
}

void TriggerElement_Text::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_dwTextID;
	}
	else
	{
		arc >> dwVersion;
		arc >> m_dwTextID;
	}
}

void TriggerElement_Weapon::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_WeaponPos;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;
		arc >> m_WeaponPos;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Weapon>(tpState);
	}
}

void TriggerElement_Game::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Game>(tpState);
	}
}

void TriggerElement_Effect::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << static_cast<int>(m_eState);
		arc << m_dwEffectID;
	}
	else
	{
		arc >> dwVersion;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Effect>(tpState);
		arc >> m_dwEffectID;
	}
}

void TriggerElement_Flag::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_dwFlagID;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;
		arc >> m_dwFlagID;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Flag>(tpState);
	}
}

void TriggerElement_Time::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;
	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_fTimeLimit;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;
		arc >> m_fTimeLimit;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Time>(tpState);
	}
}

void TriggerElement_Sound::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_TargerId;
		arc << static_cast<int>(m_eState);
	}
	else
	{
		arc >> dwVersion;
		arc >> m_TargerId;
		int tpState;
		arc >> tpState;
		m_eState = static_cast<ElementState_Sound>(tpState);
	}
}


void TriggerElement_Picture::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << m_dwPicID;
		arc << static_cast<int>(m_ePos);
	}
	else
	{
		arc >> dwVersion;
		arc >> m_dwPicID;
		int nTemp(0);
		arc >> nTemp;
		m_ePos = static_cast<ElementState_Picture>(nTemp);
	}
}


void TriggerElement_UI::Serialize(COUArchive& arc)
{
	//DWORD dwVersion = 0;
	//DWORD dwVersion = 1;    //添加界面显示相关的文本ID
	DWORD dwVersion = 2;      //添加界面显示兵力值数据

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << static_cast<int>(m_eUIIndex);
		arc << m_bShow;
		arc << m_dwTextID;
		arc << m_dwCurPartyScore;
	}
	else
	{
		arc >> dwVersion;
		int nTemp(0);
		arc >> nTemp;
		m_eUIIndex = static_cast<ElementState_UI>(nTemp);
		arc >> m_bShow;
		if(dwVersion >= 1)
		{
			arc >> m_dwTextID;

			if(dwVersion >= 2)
			{
				arc >> m_dwCurPartyScore;
			}
		}
	}
}


void TriggerElement_Items::Serialize(COUArchive& arc)
{
	DWORD dwVersion = 0;

	if ( arc.IsStoring() )
	{
		arc << dwVersion;
		arc << static_cast<int>(m_eItemsState);
		arc << m_dwItemID;
	}
	else
	{
		arc >> dwVersion;
		int nTemp(0);
		arc >> nTemp;
		m_eItemsState = static_cast<RebuildTriggerState>(nTemp);
		arc >> m_dwItemID;
	}
}

void TriggerElement_ResetPlayer::Serialize(COUArchive& arc)
{
	//DWORD dwVersion = 0;
	//DWORD dwVersion = 1;      //添加波次结束的标志
	//DWORD dwVersion = 2;      //添加Boss死亡的标志
	DWORD dwVersion = 3;         //添加AI是否进入逃跑模式的标志

	if(arc.IsStoring())
	{
		arc << dwVersion;
		arc << m_bResetLives;
		arc << m_bResetPos;
		arc << m_bBoutEnd;
		arc << m_bBossDying;
		arc << m_bAIRunning;
	}
	else
	{
		arc >> dwVersion;
		arc >> m_bResetLives;
		arc >> m_bResetPos;
		if(dwVersion >= 1)
		{
			arc >> m_bBoutEnd;
			if(dwVersion >= 2)
			{
				arc >> m_bBossDying;
				if(dwVersion >= 3)
				{
					arc >> m_bAIRunning;
				}
			}
		}
	}
}
//===========================================================

void TriggerCode::Release()
{
	UINT tpCnt;

	for ( tpCnt = 0; tpCnt < m_ConditionVec.size() ; tpCnt++)
	{
		delete m_ConditionVec[tpCnt];
	}
	m_ConditionVec.clear();

	for ( tpCnt = 0; tpCnt < m_TriggerVec.size() ; tpCnt++)
	{
		delete m_TriggerVec[tpCnt];
	}
	m_TriggerVec.clear();

	for ( tpCnt = 0; tpCnt < m_OccurrenceVec.size() ; tpCnt++)
	{
		delete m_OccurrenceVec[tpCnt];
	}
	m_OccurrenceVec.clear();

	if ( m_pTexture )
	{
		m_pTexture->Release();
	}
}

void TriggerCode::SetState(TriggerCodeState state)
{
	m_eState = state;
	//后面可能要做其他处理

}

void TriggerCode::Serialize(COUArchiveEx& arc, BYTE bVersion)
{
	arc >> m_dwID;//ID

	arc >> m_vBoundBoxMin.x;	  //场景中BoundBoxMin
	arc >> m_vBoundBoxMin.y;	  //场景中BoundBoxMin
	arc >> m_vBoundBoxMin.z;	  //场景中BoundBoxMin

	arc >> m_vBoundBoxMax.x;	  //场景中BoundBoxMax
	arc >> m_vBoundBoxMax.y;	  //场景中BoundBoxMax
	arc >> m_vBoundBoxMax.z;	  //场景中BoundBoxMax

	BOOL bActive;
	arc >> bActive;          //激活
	if ( bActive == TRUE )
	{
		m_eState = TriggerCodeState_Prepare;
	}
	else
	{
		m_eState = TriggerCodeState_Sleep;
	}

	if ( bVersion >= 1)
	{
		int tpReliveState;
		arc >> tpReliveState;
		m_AutoReliveState = static_cast<Type_AutoReliveState>(tpReliveState);
	}
	
	arc >> m_dwTextID;       //文本ID

	if ( bVersion >= 2 )
	{
		arc >> m_dwSoundID;
		arc >> m_dwAideoID;
	}

	if ( bVersion >= 3 )
	{
		arc >> m_matWorldInverse;
	}

	UINT tpElementCnt = 0;
	int codeType;
	DWORD conditionNum;
	arc >> conditionNum;
	m_ConditionVec.resize(conditionNum);
	for ( tpElementCnt = 0; tpElementCnt < m_ConditionVec.size(); tpElementCnt++)
	{
		arc >> codeType;
		m_ConditionVec[tpElementCnt] = BaseTriggerElement::QuaryTriggerCodeElement( codeType );
		m_ConditionVec[tpElementCnt]->Serialize(arc);
	}

	DWORD triggerNum;
	arc >> triggerNum;
	m_TriggerVec.resize(triggerNum);
	for ( tpElementCnt = 0; tpElementCnt < m_TriggerVec.size(); tpElementCnt++)
	{
		arc >> codeType;
		m_TriggerVec[tpElementCnt] = BaseTriggerElement::QuaryTriggerCodeElement( codeType );
		m_TriggerVec[tpElementCnt]->Serialize(arc);
	}

	DWORD occurrenceNum;
	arc >> occurrenceNum;
	m_OccurrenceVec.resize(occurrenceNum);
	for ( tpElementCnt = 0; tpElementCnt < m_OccurrenceVec.size(); tpElementCnt++)
	{
		arc >> codeType;
		m_OccurrenceVec[tpElementCnt] = BaseTriggerElement::QuaryTriggerCodeElement( codeType );
		m_OccurrenceVec[tpElementCnt]->Serialize(arc);
	}
}

//检测一个点是不是在这个包围盒之内
BOOL TriggerCode::TestIntersect(const D3DXVECTOR3& pos,BOOL yEnable /*= TRUE*/ )
{
	D3DXVECTOR3 tpPos;
	tpPos = pos;
	D3DXVec3TransformCoord(&tpPos,&tpPos,&m_matWorldInverse);
	if (yEnable)
	{
		return ( tpPos.x > m_vBoundBoxMin.x &&
			tpPos.y > m_vBoundBoxMin.y &&
			tpPos.z > m_vBoundBoxMin.z &&
			tpPos.x < m_vBoundBoxMax.x &&
			tpPos.y < m_vBoundBoxMax.y &&
			tpPos.z < m_vBoundBoxMax.z );
	} 
	else
	{
		return ( tpPos.x > m_vBoundBoxMin.x &&
			tpPos.z > m_vBoundBoxMin.z &&
			tpPos.x < m_vBoundBoxMax.x &&
			tpPos.z < m_vBoundBoxMax.z );
	}		 
}

BOOL TriggerCode::OnChackElement_Area( const BaseTriggerElement* element )
{
	const TriggerElement_Area* tpTriggerCode = dynamic_cast<const TriggerElement_Area*>( element );
	if ( GetLocalPlayer() &&
		 GetLocalPlayer()->IsPlayerStatePlaying() )
	{	
		D3DXVECTOR3 tpPlayerPos = *( GetLocalPlayer()->GetPos() );
		if ( TestIntersect( tpPlayerPos ) )
		{
			if ( tpTriggerCode->m_eState == TriggerElement_Area::ElementState_Area_Inside )
				return TRUE;
			else
				return FALSE;
		}
		else
		{
			if ( tpTriggerCode->m_eState == TriggerElement_Area::ElementState_Area_Inside )
				return FALSE;
			else
				return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL TriggerCode::OnChackElement_Physic( const BaseTriggerElement* element )
{
	const TriggerElement_Physic* tpTriggerCode = dynamic_cast<const TriggerElement_Physic*>( element );
	const CSceneObj* tpPhysObj = (const CSceneObj*)GetSceneObj( tpTriggerCode->m_TargetID );
	if ( tpPhysObj )
	{
		if ( tpPhysObj->IsPhysObj() )
		{
			if ( tpPhysObj->IsDead() )
			{
				if ( tpTriggerCode->m_eState == TriggerElement_Physic::ElementState_Physic_Die )
				{
					return TRUE;
				} 
				else
				{
					return FALSE;
				}
			}
			else
			{
				if ( tpTriggerCode->m_eState == TriggerElement_Physic::ElementState_Physic_Die )
				{
					return FALSE;
				} 
				else
				{
					return TRUE;
				}
			}
		} 
		else
		{
			ASSERT(FALSE);
			return FALSE;
		}
	}
	else
	{
		if ( tpTriggerCode->m_eState == TriggerElement_Physic::ElementState_Physic_Die )
		{
			return TRUE;
		} 
		else
		{
			return FALSE;
		}
	}
}

BOOL TriggerCode::OnChackElement_Carrier( const BaseTriggerElement* element )
{
	const TriggerElement_Carrier* tpTriggerCode = dynamic_cast<const TriggerElement_Carrier*>( element );
	if ( GetLocalPlayer() )
	{	

		if ( GetLocalPlayer()->IsInCarrier() )
		{
			if ( tpTriggerCode->m_eState == TriggerElement_Carrier::ElementState_Carrier_TakeOn )
				return TRUE;
			else
				return FALSE;
		}
		else
		{
			if ( tpTriggerCode->m_eState == TriggerElement_Carrier::ElementState_Carrier_Leave )
				return TRUE;
			else
				return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

void TriggerCode::ChackGameCtrl( DWORD keyId , int& gameKeyId01, int& gameKeyId02 )
{
	switch( keyId )
	{
	case 0://上
		gameKeyId01 = (int)cfg_Game_dwForward;
		gameKeyId02 = (int)cfg_Game_dwForward02;
		return ;
	case 1://下
		gameKeyId01 = (int)cfg_Game_dwBackward;
		gameKeyId02 = (int)cfg_Game_dwBackward02;
		break;
	case 2://左
		gameKeyId01 = (int)cfg_Game_dwLeftMove;
		gameKeyId02 = (int)cfg_Game_dwLeftMove02;
		break;
	case 3://右
		gameKeyId01 = (int)cfg_Game_dwRightMove;
		gameKeyId02 = (int)cfg_Game_dwRightMove02;
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}
}

BOOL TriggerCode::OnChackElement_KeyControl( const BaseTriggerElement* element )
{
	const TriggerElement_KeyControl* tpTriggerCode = dynamic_cast<const TriggerElement_KeyControl*>( element );

	int gameKeyId01 = -1;
	int gameKeyId02 = -1;
	ChackGameCtrl( tpTriggerCode->m_dwKeyId , gameKeyId01, gameKeyId02 );

	switch( tpTriggerCode->m_eState )
	{
	case TriggerElement_KeyControl::ElementState_KeyControl_Click:
		return ( ( gameKeyId01 >= 0 &&
			GetKBMng()->IsKeyClicked( gameKeyId01 ) ) ||
			( gameKeyId02 >= 0 &&
			GetKBMng()->IsKeyClicked( gameKeyId02 ) ) );

	case TriggerElement_KeyControl::ElementState_KeyControl_Down:
		return ( ( gameKeyId01 >= 0 &&
			GetKBMng()->IsKeyUpToDown( gameKeyId01 ) ) ||
			( gameKeyId02 >= 0 &&
			GetKBMng()->IsKeyUpToDown( gameKeyId02 ) ) );

	case TriggerElement_KeyControl::ElementState_KeyControl_Up:
		return ( ( gameKeyId01 >= 0 &&
			GetKBMng()->IsKeyDownToUp( gameKeyId01 ) ) ||
			( gameKeyId02 >= 0 &&
			GetKBMng()->IsKeyDownToUp( gameKeyId02 ) ) );

	default:
		break;
	}
	return FALSE;
}

BOOL TriggerCode::OnChackElement_PlayerState( const BaseTriggerElement* element )
{
	const TriggerElement_PlayerState* tpTriggerCode = dynamic_cast<const TriggerElement_PlayerState*>( element );

	if ( GetLocalPlayer() )
	{	
		BOOL soldierStanceChack = TRUE;
		BOOL teamColorChack = TRUE;
		BOOL kitClassChack = TRUE;
		BOOL eventChack = TRUE;

		

		if( tpTriggerCode->m_eState != TriggerElement_PlayerState::ElementState_PlayerState_Whatever )
		{
			switch ( GetLocalPlayer()->GetSoldierStance() )
			{
			case SOLDIER_STANCE_STAND:
				{
					if ( tpTriggerCode->m_eState == TriggerElement_PlayerState::ElementState_PlayerState_Stand )
						soldierStanceChack = TRUE;
					else
						soldierStanceChack = FALSE;
				}
				break;
			case SOLDIER_STANCE_CROUCH:
				{
					if ( tpTriggerCode->m_eState == TriggerElement_PlayerState::ElementState_PlayerState_Crouch )
						soldierStanceChack = TRUE;
					else
						soldierStanceChack = FALSE;
				}
				break;
			case SOLDIER_STANCE_PRONE:
				{
					if ( tpTriggerCode->m_eState == TriggerElement_PlayerState::ElementState_PlayerState_Prone )
						soldierStanceChack = TRUE;
					else
						soldierStanceChack = FALSE;
				}
				break;
			default:
				soldierStanceChack = FALSE;
			}

			//[2011-4-27][郑怡曼][检测是否存活]
			if(tpTriggerCode->m_eState == TriggerElement_PlayerState::ElementState_PlayerState_Alive)
			{
				if(GetLocalPlayer() && GetLocalPlayer()->GetHealthState() == PLAYER_HEALTH_STATE_NORMAL)
				{
					soldierStanceChack = TRUE;
				}
				else
				{
					soldierStanceChack = FALSE;
				}
			}
		}

		if ( tpTriggerCode->m_eTeamColor == TEAM_COLOR_NORMAL ||
			 GetLocalPlayer()->GetTeamColor() == tpTriggerCode->m_eTeamColor )
		{
			teamColorChack = TRUE;
		}
		else
		{
			teamColorChack = FALSE;
		}

		if( tpTriggerCode->m_eKitClass == KIT_CLASS_NUM ||
			tpTriggerCode->m_eKitClass == GetLocalPlayer()->GetKitClass())
		{
			kitClassChack = TRUE;
		}
		else
			kitClassChack = FALSE;


		TriggerEvent eTempEvent(TriggerEvent_Invalide);
		switch( tpTriggerCode->m_eEvent)
		{
		case TriggerElement_PlayerState::ElementState_PlayerEvent_Repair:
			eTempEvent = TriggerEvent_Repair;
			break;
		case TriggerElement_PlayerState::ElementState_PlayerEvent_Medical:
			eTempEvent = TriggerEvent_Medical;
			break;
		case TriggerElement_PlayerState::ElementState_PlayerEvent_Ammu:
			eTempEvent = TriggerEvent_Ammu;
			break;
		case TriggerElement_PlayerState::ElementState_PlayerEvent_relive:
			eTempEvent = TriggerEvent_relive;
			break;
		case TriggerElement_PlayerState::ElementState_PlayerEvent_Uav:
			eTempEvent = TriggerEvent_Uav;
			break;
		case TriggerElement_PlayerState::ElementState_PlayerEvent_LandMine:
			eTempEvent = TriggerEvent_Landmine;
			break;
		case TriggerElement_PlayerState::ElementState_PlayerEvent_Placemine:
			eTempEvent = TriggerEvent_Placemine;
			break;
		default:
			eTempEvent = TriggerEvent_Invalide;
		}
		if( eTempEvent == TriggerEvent_Invalide || 
			(TriggerMng::GetSingletonPtr() && TriggerMng::GetSingletonPtr()->IfHappenTriggerEvent(eTempEvent) ) )
		{
			eventChack = TRUE;
		}
		else
			eventChack = FALSE;

		return teamColorChack && soldierStanceChack && kitClassChack && eventChack;
	}
	else
	{
		return FALSE;
	}
}

BOOL TriggerCode::OnChackElement_Trigger( const BaseTriggerElement* element )
{
	const TriggerElement_Trigger* tpTriggerCode = dynamic_cast<const TriggerElement_Trigger*>( element );

	TriggerCode* tpTargetTrigger = NULL;
	//查找
	if ( TriggerMng::GetSingletonPtr() )
	{
		tpTargetTrigger = TriggerMng::GetSingletonPtr()->FindTrigger( tpTriggerCode->m_TargerId );
		if ( tpTargetTrigger )
		{
			switch( tpTargetTrigger->GetState() )
			{
			case TriggerCodeState_Sleep:
				{
					if ( tpTriggerCode->m_eState == TriggerElement_Trigger::ElementState_Trigger_Sleep )
						return TRUE;
					else
						return FALSE;
				}
				break;

			case TriggerCodeState_Prepare:
			case TriggerCodeState_Active:
				{
					if ( tpTriggerCode->m_eState == TriggerElement_Trigger::ElementState_Trigger_Wake )
						return TRUE;
					else
						return FALSE;
				}
				break;

			default:
				return FALSE;
			}
		} 
		else
		{
			return FALSE;
		}
	}
	else 
		return FALSE;
}


BOOL TriggerCode::OnChackElement_Game( const BaseTriggerElement* element )
{
	const TriggerElement_Game* tpGameCode = dynamic_cast<const TriggerElement_Game*>( element );

	if(GetHost() && GetHost()->GetCompetitionRulesPtr() )
	{
		switch ( tpGameCode->m_eState )
		{
		case TriggerElement_Game::ElementState_Game_Start:
			{
				if ( GetHost()->GetCompetitionRulesPtr()->GetGameState() == state_Playing  )
					return TRUE;
				else
					return FALSE;
			}
			break;
		case TriggerElement_Game::ElementState_Game_Win:
			{
				if ( MATCH_RESULT_WIN == GetHost()->GetCompetitionRulesPtr()->GetMatchResult(GetLocalPlayer()->GetTeamColor()) )
					return TRUE;
				else
					return FALSE;
			}
			break;
		case TriggerElement_Game::ElementState_Game_Lost:
			{
				if ( MATCH_RESULT_LOSS == GetHost()->GetCompetitionRulesPtr()->GetMatchResult(GetLocalPlayer()->GetTeamColor()) )
					return TRUE;
				else
					return FALSE;
			}
			break;
		default:
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL TriggerCode::OnChackElement_Weapon( const BaseTriggerElement* element )
{
	const TriggerElement_Weapon* tpWeaponCode = dynamic_cast<const TriggerElement_Weapon*>( element );

	if ( GetLocalPlayer() )
	{	
		switch ( tpWeaponCode->m_eState )
		{
		case TriggerElement_Weapon::ElementState_Weapon_Enable:
			{
				if ( GetLocalPlayer()->GetPosWeapon( static_cast<ENUM_EQUIP_POS>( tpWeaponCode->m_WeaponPos ) )
					&& GetLocalPlayer()->IsCanSelectWeapon(static_cast<ENUM_EQUIP_POS>( tpWeaponCode->m_WeaponPos )) )
					return TRUE;
				else
					return FALSE;
			}
			break;
		case TriggerElement_Weapon::ElementState_Weapon_Destroy:
			{
				if ( GetLocalPlayer()->GetPosWeapon( static_cast<ENUM_EQUIP_POS>( tpWeaponCode->m_WeaponPos ) ) 
					&& GetLocalPlayer()->IsCanSelectWeapon(static_cast<ENUM_EQUIP_POS>( tpWeaponCode->m_WeaponPos )) )
					return FALSE;
				else
					return TRUE;
			}
			break;
		case TriggerElement_Weapon::ElementState_Weapon_Change:
			{
				if ( GetLocalPlayer()->GetCurrentEquipPos() == static_cast<ENUM_EQUIP_POS>( tpWeaponCode->m_WeaponPos ) )
					return TRUE;
				else
					return FALSE;
			}
			break;
		default:
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL TriggerCode::OnChackElement_Flag( const BaseTriggerElement* element )
{
	const TriggerElement_Flag* tpFlagCode = dynamic_cast<const TriggerElement_Flag*>( element );

	CFlag* tpFlagObj = (CFlag*)GetFlag( tpFlagCode->m_dwFlagID );
	if ( tpFlagObj )
	{
		if ( tpFlagCode->m_eState == TriggerElement_Flag::ElementState_Flag_RedColor )
		{
			return tpFlagObj->GetCurrentTeamColor() == TEAM_COLOR_RED;
		}
		else if ( tpFlagCode->m_eState == TriggerElement_Flag::ElementState_Flag_BuleColor )
		{
			return tpFlagObj->GetCurrentTeamColor() == TEAM_COLOR_BLUE;
		}	
		else
		{
			ASSERT(FALSE);
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL TriggerCode::OnChackElement_Time( BaseTriggerElement* element ,FLOAT fElapsedTime)
{
    TriggerElement_Time* tpTimeCode = dynamic_cast<TriggerElement_Time*>( element );

	if ( m_eState == TriggerCodeState_Prepare || m_eState == TriggerCodeState_Active)
	{
		//if(m_bChackTriggerEnable)
		tpTimeCode->m_fCurPassTime += fElapsedTime;
	}
	else
	{
		tpTimeCode->m_fCurPassTime = 0;
	}

	switch ( tpTimeCode->m_eState )
	{
	case TriggerElement_Time::ElementState_Time_Greater:
		{
			return tpTimeCode->m_fCurPassTime > tpTimeCode->m_fTimeLimit;
		}
		break;
	case TriggerElement_Time::ElementState_Time_Less:
		{
			return tpTimeCode->m_fCurPassTime < tpTimeCode->m_fTimeLimit;
		}
		break;
	default:
		return TRUE;
	}
}

BOOL TriggerCode::OnChackElement_Items( const BaseTriggerElement* element )
{
	const TriggerElement_Items* tpItemsCode = dynamic_cast<const TriggerElement_Items*>( element );

	CObjectRebuildBase* tpRebuildObj(NULL);
	if ( CObjectRebuildManager::GetSingletonPtr() )
		tpRebuildObj = CObjectRebuildManager::GetSingletonPtr()->GetRebuildObjectPtr(tpItemsCode->m_dwItemID);
	
	if ( tpRebuildObj )
	{
		if ( tpItemsCode->m_eItemsState == RebuildTriggerState_Activation )
		{
			return tpRebuildObj->GetInfo()->m_eCurState == RebuildTriggerState_Activation;
		}
		else if ( tpItemsCode->m_eItemsState == RebuildTriggerState_Dead )
		{
			return tpRebuildObj->GetInfo()->m_eCurState == RebuildTriggerState_Dead;
		}	
		else
		{
			ASSERT(FALSE);
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL TriggerCode::OnChackElement_CampDeath(const BaseTriggerElement* element)
{
	const TriggerElement_CampDeath* tpCampDeathCode = dynamic_cast<const TriggerElement_CampDeath*>(element);
	switch(tpCampDeathCode->m_eCategory)
	{
	case TriggerElement_CampDeath::ElementState_Category_Player:
		{
			if(tpCampDeathCode->m_eCamp == TriggerElement_CampDeath::ElementState_Camp_Red)
			{
				//如果数目为0...则表明触发条件为要AI全部死光
				if(tpCampDeathCode->m_dwKillNum == 0)
				{
					if(GetPlayerManager())
					{
						if(GetPlayerManager()->GetLivingAISoldiersCount(TEAM_COLOR_RED) == 0)
						{
							return TRUE;
						}
					}
				}
				else if((DWORD)(GetHost()->m_sCampDeath.nRedTeamNum) >= tpCampDeathCode->m_dwKillNum)
					return TRUE;
			}
			else if(tpCampDeathCode->m_eCamp == TriggerElement_CampDeath::ElementState_Camp_Blue)
			{
				if(tpCampDeathCode->m_dwKillNum == 0)
				{
					if(GetPlayerManager())
					{
						if(GetPlayerManager()->GetLivingAISoldiersCount(TEAM_COLOR_BLUE) == 0)
						{
							return TRUE;
						}
					}
				}
				else if((DWORD)(GetHost()->m_sCampDeath.nBlueTeamNum) >= tpCampDeathCode->m_dwKillNum)
					return TRUE;
			}
			else if(tpCampDeathCode->m_eCamp == TriggerElement_CampDeath::ElementState_Camp_Normal)
			{
				if((DWORD)(GetHost()->m_sCampDeath.nNormalTeamNum) >= tpCampDeathCode->m_dwKillNum)
				{
					return TRUE;
				}
			}
		}
		break;
	case TriggerElement_CampDeath::ElementState_Category_Prop:   //未需求
		{
			return FALSE;
		}
		break;
	default:
		{
			ASSERT(FALSE);
			return FALSE;
		}
	}
	return FALSE;
}



//--- 事件处理。。。------
void TriggerCode::OnDealElement_Trigger( const BaseTriggerElement* element )
{
	const TriggerElement_Trigger* tpTriggerCode = dynamic_cast<const TriggerElement_Trigger*>( element );

	TriggerCode* tpTargetTrigger = NULL;
	//查找
	if ( TriggerMng::GetSingletonPtr() )
	{
		tpTargetTrigger = TriggerMng::GetSingletonPtr()->FindTrigger( tpTriggerCode->m_TargerId );
		if ( tpTargetTrigger )
		{
			switch( tpTriggerCode->m_eState )
			{
			case TriggerElement_Trigger::ElementState_Trigger_Sleep:
				{
					tpTargetTrigger->SetState(TriggerCodeState_Sleep);
				}
				break;

			case TriggerElement_Trigger::ElementState_Trigger_Wake:
				{
					tpTargetTrigger->SetState(TriggerCodeState_Prepare);
				}
				break;
			}
		}
	}
}

void TriggerCode::OnDealElement_Physic( const BaseTriggerElement* element )
{
	const TriggerElement_Physic* tpTriggerCode = dynamic_cast<const TriggerElement_Physic*>( element );
	CSceneObj* tpPhysObj = (CSceneObj*)GetSceneObj( tpTriggerCode->m_TargetID );
	if ( tpPhysObj )
	{
		if ( tpPhysObj->IsPhysObj() )
		{
			if ( tpPhysObj->IsDead() )
			{
				return;//暂时没办法复活
			}
			else
			{
				if( tpTriggerCode->m_eState == TriggerElement_Physic::ElementState_Physic_Die )
				{
					tpPhysObj->Die(FALSE);
				}
			}
		}
		else
			ASSERT(FALSE);
	}
}

void TriggerCode::OnDealElement_Text( const BaseTriggerElement* element )
{
	const TriggerElement_Text* tpTextCode = dynamic_cast<const TriggerElement_Text*>( element );
	m_dwTextID = tpTextCode->m_dwTextID;
}

void TriggerCode::OnDealElement_Picture( const BaseTriggerElement* element )
{
	const TriggerElement_Picture* tpPicCode = dynamic_cast<const TriggerElement_Picture*>( element );
	m_dwPicID = tpPicCode->m_dwPicID;
	m_ePicturePos = tpPicCode->m_ePos;
}

void TriggerCode::OnDealElement_UI( const BaseTriggerElement* element )
{
	const TriggerElement_UI* tpPicCode = dynamic_cast<const TriggerElement_UI*>( element );
	switch(tpPicCode->m_eUIIndex)
	{
	case TriggerElement_UI::ElementState_UI_Normal:
	case TriggerElement_UI::ElementState_UI_Boss:
		{
			if(CRaceResultPVE::GetSingletonPtr())
				CRaceResultPVE::GetSingletonPtr()->DealWithPVEUI(tpPicCode);
		}break;
	default:
		{
			if( CTraingUIDlgMng::GetSingletonPtr())
				CTraingUIDlgMng::GetSingletonPtr()->DealWithUI(tpPicCode->m_eUIIndex,tpPicCode->m_bShow);
		}break;
	}
}

extern GAMESYSTEM_API PFUN_CHANGEKITCLASS g_lpChangeKitClass;
void TriggerCode::OnDealElement_Player(const BaseTriggerElement* element )
{
	const TriggerElement_PlayerState* tpTriggerCode = dynamic_cast<const TriggerElement_PlayerState*>( element );

	if ( GetLocalPlayer() )
	{	
		switch ( tpTriggerCode->m_eState )
		{
		case TriggerElement_PlayerState::ElementState_PlayerState_Dead:
			{//杀死本地玩家
				//SDamageInfo Info;
				//Info.m_AttckerCRID		= INVALID_CRID;
				//Info.m_FromPlayerCRID	= INVALID_CRID;
				//Info.m_dwWeaponEquipID	= -1;//装备ID
				//Info.m_vPosition		= *GetLocalPlayer()->GetPos();
				//Info.m_fDamage			= 10000.f;
				//Info.m_dwFlag			= DMG_FLAG_KILLSELF;
				//GetLocalPlayer()->PlayerOnTakeDamage(Info); 
				if(GetPlayerManager())
					GetPlayerManager()->KillMySelf();
			}
			break;
		}

		//处理兵种设定
		if( tpTriggerCode->m_eKitClass != KIT_CLASS_NUM)
		{
			if ( g_lpChangeKitClass )
			{
				g_lpChangeKitClass(tpTriggerCode->m_eKitClass);
			}
		}
	}
}

void TriggerCode::OnDealElement_Weapon( const BaseTriggerElement* element )
{
	const TriggerElement_Weapon* tpWeaponCode = dynamic_cast<const TriggerElement_Weapon*>( element );

	if ( GetLocalPlayer() )
	{	
		switch ( tpWeaponCode->m_eState )
		{
		case TriggerElement_Weapon::ElementState_Weapon_Enable:
			{
				for ( int tpCnt = tpWeaponCode->m_WeaponPos + 1 ; tpCnt <= static_cast<int>( EQUIP_POS_SPECIAL_B ) ; tpCnt++ )
				{
					GetLocalPlayer()->ReleasePosWeapon( static_cast<ENUM_EQUIP_POS>( tpCnt ) );
				}
				if ( FAILED( GetLocalPlayer()->TrySwitchWeaponTo( static_cast<ENUM_EQUIP_POS>( tpWeaponCode->m_WeaponPos ) ) ) )
				{
					GetLocalPlayer()->TrySwitchWeaponTo( EQUIP_POS_KNIFE );
				}
			}
			break;

		case TriggerElement_Weapon::ElementState_Weapon_Destroy:
			{
				GetLocalPlayer()->ReleasePosWeapon( static_cast<ENUM_EQUIP_POS>( tpWeaponCode->m_WeaponPos ) );
			}
			break;

		case TriggerElement_Weapon::ElementState_Weapon_Change:
			{
				GetLocalPlayer()->TrySwitchWeaponTo( static_cast<ENUM_EQUIP_POS>( tpWeaponCode->m_WeaponPos ) );
			}
			break;
		}
	}
}

void TriggerCode::OnDealElement_Game( const BaseTriggerElement* element )
{
	const TriggerElement_Game* tpGameCode = dynamic_cast<const TriggerElement_Game*>( element );

	if ( GetHost() &&  
		 GetHost()->GetCompetitionRulesPtr() &&
		 GetLocalPlayer() )
	{	
		switch ( tpGameCode->m_eState )
		{
		case TriggerElement_Game::ElementState_Game_Win:
			{
				GetHost()->GetCompetitionRulesPtr()->SetRoundResult( GetLocalPlayer()->GetTeamColor() );
			}
			break;

		case TriggerElement_Game::ElementState_Game_Lost:
			{
				switch( GetLocalPlayer()->GetTeamColor() )
				{
				case TEAM_COLOR_RED:
					GetHost()->GetCompetitionRulesPtr()->SetRoundResult( TEAM_COLOR_BLUE );
					break;
				case TEAM_COLOR_BLUE:
					GetHost()->GetCompetitionRulesPtr()->SetRoundResult( TEAM_COLOR_RED );
					break;
				default:
				    break;
				}
			}
			break;

		case TriggerElement_Game::ElementState_Game_Start:
			{
				GetHost()->GetCompetitionRulesPtr()->SetGameState( state_Playing );
			}
			break;

		case TriggerElement_Game::ElementState_Game_Pause:
			{
				GetHost()->GetCompetitionRulesPtr()->SetGameState( state_Pause );
			}
			break;

		}
	}
}

void TriggerCode::OnDealElement_Effect( const BaseTriggerElement* element )
{
	const TriggerElement_Effect* tpEffectCode = dynamic_cast<const TriggerElement_Effect*>( element );
	CSceneObj* tpSceneObj = (CSceneObj*)GetSceneObj( tpEffectCode->m_dwEffectID );
	if ( tpSceneObj )
	{
		if ( tpSceneObj->GetObjType() == OT_EFFECTOBJ)
		{
			CEffectObject* tpEffectObj = dynamic_cast<CEffectObject*>(tpSceneObj);
			if ( tpEffectObj->IsDead() )
			{
				return;//暂时没办法复活
			}
			else
			{
				switch( tpEffectCode->m_eState)
				{
				case TriggerElement_Effect::ElementState_Effect_Stop :
					{
						tpEffectObj->GetGmaEffectPlayer()->Stop();
					}
					break;

				case TriggerElement_Effect::ElementState_Effect_Play :
					{
						tpEffectObj->GetGmaEffectPlayer()->Play(GetAppTime());
					}
					break;
				}
			}
		}
		else
			ASSERT(FALSE);
	}
}

void TriggerCode::OnDealElement_Flag( const BaseTriggerElement* element )
{
	const TriggerElement_Flag* tpFlagCode = dynamic_cast<const TriggerElement_Flag*>( element );

	CFlag* tpFlagObj = GetFlag( tpFlagCode->m_dwFlagID );
	if ( tpFlagObj )
	{
		if ( tpFlagCode->m_eState == TriggerElement_Flag::ElementState_Flag_CurRelive )
		{
			GetFlagsManager()->SetLocalReliveFlag(tpFlagCode->m_dwFlagID);
		}
		else if( tpFlagCode->m_eState == TriggerElement_Flag::ElementState_Flag_RedColor)
		{
			tpFlagObj->OnChangeFlag(TEAM_COLOR_RED);
			if(!IsHostMasterClient())
			{
				SSyncCTOHChangeFlagColor sFlagStateInfo ;
				sFlagStateInfo.m_dwServerID = GetHost()->GetHostGlobalID();
				sFlagStateInfo.m_dwClientID = GetLocalPlayer()->GetGlobalID();
				sFlagStateInfo.m_wFlagID = tpFlagCode->m_dwFlagID;
				sFlagStateInfo.m_FlagTeamColor = TEAM_COLOR_RED;
				SendPeerMsg(MSMI_CTOH_CHANGE_FLAG_COLOR, sFlagStateInfo, sFlagStateInfo.m_dwServerID);
			}
		}
		else if( tpFlagCode->m_eState == TriggerElement_Flag::ElementState_Flag_BuleColor)
		{
			tpFlagObj->OnChangeFlag(TEAM_COLOR_BLUE);
			if(!IsHostMasterClient())
			{
				SSyncCTOHChangeFlagColor sFlagStateInfo ;
				sFlagStateInfo.m_dwServerID = GetHost()->GetHostGlobalID();
				sFlagStateInfo.m_dwClientID = GetLocalPlayer()->GetGlobalID();
				sFlagStateInfo.m_wFlagID = tpFlagCode->m_dwFlagID;
				sFlagStateInfo.m_FlagTeamColor = TEAM_COLOR_BLUE;
				SendPeerMsg(MSMI_CTOH_CHANGE_FLAG_COLOR, sFlagStateInfo, sFlagStateInfo.m_dwServerID);
			}
		}
		else if(tpFlagCode->m_eState == TriggerElement_Flag::ElementState_Flag_Middle)
		{
			tpFlagObj->OnChangeFlag(TEAM_COLOR_NORMAL);
			if(!IsHostMasterClient())
			{
				SSyncCTOHChangeFlagColor sFlagStateInfo ;
				sFlagStateInfo.m_dwServerID = GetHost()->GetHostGlobalID();
				sFlagStateInfo.m_dwClientID = GetLocalPlayer()->GetGlobalID();
				sFlagStateInfo.m_wFlagID = tpFlagCode->m_dwFlagID;
				sFlagStateInfo.m_FlagTeamColor = TEAM_COLOR_NORMAL;
				SendPeerMsg(MSMI_CTOH_CHANGE_FLAG_COLOR, sFlagStateInfo, sFlagStateInfo.m_dwServerID);
			}
		}
	}
}

void TriggerCode::OnDealElement_CampDeath(const BaseTriggerElement* element)
{
	const TriggerElement_CampDeath* tpCode = dynamic_cast<const TriggerElement_CampDeath*>(element);

	switch(tpCode->m_eCategory)
	{
	case TriggerElement_CampDeath::ElementState_Category_Player:
		{
			if(tpCode->m_eCamp == TriggerElement_CampDeath::ElementState_Camp_Red)
			{
				if(GetHost())
					GetHost()->m_sCampDeath.nRedTeamNum = 0;
			}
			if(tpCode->m_eCamp == TriggerElement_CampDeath::ElementState_Camp_Blue)
			{
				if(GetHost())
					GetHost()->m_sCampDeath.nBlueTeamNum = 0;
			}
			if(tpCode->m_eCamp == TriggerElement_CampDeath::ElementState_Camp_Normal)
			{
				if(GetHost())
					GetHost()->m_sCampDeath.nNormalTeamNum = 0;
			}
		}
		break;
	case TriggerElement_CampDeath::ElementState_Category_Prop:
		break;
	default:
		break;
	}
}

void TriggerCode::OnDealElement_ResetPlayer(const BaseTriggerElement* element)
{
	const TriggerElement_ResetPlayer* tpCode = dynamic_cast<const TriggerElement_ResetPlayer*>(element);
	if(tpCode->m_bResetLives == TRUE)
	{
		//重置复活次数 并通知其他玩家当前的命数
		DWORD dwDefaultLives = GetHost()->GetCompetitionRulesPtr() ->GetCurrentGameRule().m_nReliveTimes;
		DWORD dwKilledNum = GetLocalPlayer()->GetMatchInfo().m_wBeKilledNumber;
		DWORD dwUsingReliveItemNum(0);
		CPVECompetitionRules* temp_CTDMRules = dynamic_cast<CPVECompetitionRules*>(GetHost()->GetCompetitionRulesPtr());
		if(temp_CTDMRules != NULL)
			dwUsingReliveItemNum = temp_CTDMRules->getBeginReliveItemNums();
		DWORD curReliveItemNums(0);
		curReliveItemNums = GetBasePlayer()->GetSumReliveToolsItemNum();
		//有效复活道具个数
		int nWorkReliveNums(0);
		nWorkReliveNums = dwKilledNum - dwDefaultLives;
		if(nWorkReliveNums < 0)
			nWorkReliveNums = 0;
		int nleftReliveNums(0);
		nleftReliveNums = dwUsingReliveItemNum - curReliveItemNums - nWorkReliveNums;
		if(nleftReliveNums < 0)
			nleftReliveNums = 0;
		GetLocalPlayer()->SetReliveTimes(nleftReliveNums + dwDefaultLives);
		SPlayerUseReliveTools reliveInfo;
		reliveInfo.m_dwPlayerGlobalID = GetLocalPlayer()->GetGlobalID();
		reliveInfo.m_nReliveTimes = GetLocalPlayer()->GetReliveTimes();
		reliveInfo.m_dwReliveToolsNum = GetLocalPlayer()->GetReliveToolsNum();
		SendPeerMsg(MSMI_USE_RELIVETOOLS, reliveInfo);
	}
	if(tpCode->m_bResetPos == TRUE)
	{
		//重置玩家
		GetHost()->TryToResetLocalPlayer();
	}
	if(tpCode->m_bBoutEnd == TRUE)
	{
		//波次结束
		if(CRaceResultPVE::GetSingletonPtr())
		{
			DWORD tmp_curRounds = CRaceResultPVE::GetSingletonPtr()->GetCurRounds();
			CRaceResultPVE::GetSingletonPtr()->SetCurRounds(tmp_curRounds + 1);

			//波次结束清空击杀情况
			if(GetHost())
			{
				GetHost()->m_sCampDeath.nRedTeamNumSum = 0;
				GetHost()->m_sCampDeath.nBlueTeamNumSum = 0;
				GetHost()->m_sCampDeath.nNormalTeamNumSum = 0;
			}

			if(CRaceResultPVE::GetSingletonPtr())
			{
				CRaceResultPVE::GetSingletonPtr()->SetKillNum(0);
				if(CRaceResultPVE::GetSingletonPtr()->GetBossState() == KILLED)
				{
					CRaceResultPVE::GetSingletonPtr()->SetBossState(UNDISAPPEAR);
				}
			}
		}
	}
	//[2011-4-27][郑怡曼][Boss死亡]
	if(tpCode->m_bBossDying ==TRUE)
	{
		if(CRaceResultPVE::GetSingletonPtr())
		{
			CRaceResultPVE::GetSingletonPtr()->SetBossState(KILLED);
		}
	}

	//[2011-4-27][郑怡曼][AI是否进入逃跑模式]
	if(tpCode->m_bAIRunning == TRUE)
	{
		if(GetPlayerManager())
		{
			GetPlayerManager()->UpateAISoldiersEscapeState();
		}
	}
}

void TriggerCode::OnDealElement_Sound( const BaseTriggerElement* element )
{
	const TriggerElement_Sound* tpSoundCode = dynamic_cast<const TriggerElement_Sound*>( element );
	//音效处理
	if( tpSoundCode->m_eState == TriggerElement_Sound::ElementState_Sound_Wake)
	{
		GetMediaCentral()->PlayUISound(tpSoundCode->m_TargerId);
	}
	
}

// 检测条件
BOOL TriggerCode::OnChackCondition( FLOAT fElapsedTime )
{
	for ( UINT tpCnt = 0; tpCnt < m_ConditionVec.size(); tpCnt++ )
	{
		switch( m_ConditionVec[tpCnt]->GetType() )
		{
		case TriggerType_Area:
			{
				if ( OnChackElement_Area( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Physic:
			{
				if ( OnChackElement_Physic( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Carrier:
			{
				if ( OnChackElement_Carrier( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_PlayerState:
			{
				if ( OnChackElement_PlayerState( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Trigger:
			{
				if ( OnChackElement_Trigger( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Weapon:
			{
				if ( OnChackElement_Weapon( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Flag:
			{
				if ( OnChackElement_Flag( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Time:
			{
				if ( OnChackElement_Time( m_ConditionVec[tpCnt] , fElapsedTime ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Game:
			{
				if ( OnChackElement_Game( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Items:
			{
				if ( OnChackElement_Items( m_ConditionVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case  TriggerType_CampDeath:
			{
				if(OnChackElement_CampDeath(m_ConditionVec[tpCnt]) == FALSE)
				{
					return FALSE;
				}
			}break;

		default:
			ASSERT(FALSE);
			break;
		}
	}
	return TRUE;
}

// 检测触发
BOOL TriggerCode::OnChackTrigger()
{
	for ( UINT tpCnt = 0; tpCnt < m_TriggerVec.size(); tpCnt++ )
	{
		switch( m_TriggerVec[tpCnt]->GetType() )
		{
		case TriggerType_Area:
			{
				if ( OnChackElement_Area( m_TriggerVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Physic:
			{
				if ( OnChackElement_Physic( m_TriggerVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_KeyControl:
			{
				if ( OnChackElement_KeyControl( m_TriggerVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Carrier:
			{
				if ( OnChackElement_Carrier( m_TriggerVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Weapon:
			{
				if ( OnChackElement_Weapon( m_TriggerVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
		case TriggerType_Flag:
			{
				if ( OnChackElement_Flag( m_TriggerVec[tpCnt] ) == FALSE )
				{
					return FALSE;
				}
			}
			break;
			case TriggerType_PlayerState:
			{
				if ( OnChackElement_PlayerState( m_TriggerVec[tpCnt] ) == FALSE )
				{
				return FALSE;
				}
			}
			break;
			case TriggerType_Trigger:
			{
				if ( OnChackElement_Trigger( m_TriggerVec[tpCnt] ) == FALSE )
				{
				return FALSE;
				}
			}
			case TriggerType_Game:
				{
					if ( OnChackElement_Game( m_TriggerVec[tpCnt] ) == FALSE )
					{
						return FALSE;
					}
				}
			break;
			case TriggerType_Items:
				{
					if ( OnChackElement_Items( m_TriggerVec[tpCnt] ) == FALSE )
					{
						return FALSE;
					}
				}
				break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
	return TRUE;
}

// 处理事件
void TriggerCode::OnDoOccurrence()
{
	for ( UINT tpCnt = 0; tpCnt < m_OccurrenceVec.size(); tpCnt++ )
	{
		switch( m_OccurrenceVec[tpCnt]->GetType() )
		{
		case TriggerType_Physic:
			OnDealElement_Physic( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_Text:
			OnDealElement_Text( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_Trigger:
			OnDealElement_Trigger( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_Weapon:
			OnDealElement_Weapon( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_Game:
			OnDealElement_Game( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_Effect:
			OnDealElement_Effect( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_Flag:
			OnDealElement_Flag( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_Sound:
			OnDealElement_Sound( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_Picture:
			OnDealElement_Picture( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_PlayerState:
			OnDealElement_Player( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_UI:
			OnDealElement_UI( m_OccurrenceVec[tpCnt] );
			break;
		case TriggerType_ResetPlayer:
			OnDealElement_ResetPlayer(m_OccurrenceVec[tpCnt]);
			break;
		case TriggerType_CampDeath:
			OnDealElement_CampDeath(m_OccurrenceVec[tpCnt]);
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}

	//to be continue...触发声音和视频
	if( m_dwSoundID  != -1 )
	{
		if(GetMediaCentral())
			GetMediaCentral()->PlayUISound(m_dwSoundID);
	}

	if( m_dwAideoID >= 1 && m_dwAideoID <= 8 ) 
	{
		GetIntroductoryVideoMngPtr()->UpdateVideoInGame( m_dwAideoID );
	}
	else if (  m_dwAideoID >= 9 && m_dwAideoID <= 21  )
	{
		GetOtherVideoDlgPtr()->UpdateVideoInGame( m_dwAideoID );
	}
}

void TriggerCode::Simulate(FLOAT fElapsedTime)
{
	m_bChackConditionEnable = FALSE;
	m_bChackTriggerEnable = FALSE;

	//只有是Prapare状态才进行触发判定
	if ( m_eState == TriggerCodeState_Prepare )
	{
		//触发判定和条件判定通过 ---- 注意这两个判定的次序不能更改
		m_bChackTriggerEnable = OnChackTrigger();
		m_bChackConditionEnable = OnChackCondition( fElapsedTime );
		if ( m_bChackTriggerEnable &&
			 m_bChackConditionEnable )
		{

			OnDoOccurrence();
			SetState(TriggerCodeState_Active);
		}
	}
	else if( m_eState == TriggerCodeState_Active )
	{
		m_bChackConditionEnable = OnChackCondition( fElapsedTime );
		if( m_bChackConditionEnable  == FALSE )//如果是自动休眠的,则检查条件
		{
			switch ( m_AutoReliveState )
			{	
			case Type_AutoReliveState_None:
				break;
			case Type_AutoReliveState_Sleep:
				SetState(TriggerCodeState_Sleep);
				break;
			case Type_AutoReliveState_Prepare:
				SetState(TriggerCodeState_Prepare);
				break;
			default:
				ASSERT(FALSE);
				break;
			} 
		}
	}
}

GAMESYSTEM_API void RenderMiddleScreenTexture(LPGFX3D_DIRECT3DDEVICE pDevice, LPGFX3D_DIRECT3DTEXTURE lpTexture , FLOAT fAlpha );
GAMESYSTEM_API void RenderRateTexture(LPGFX3D_DIRECT3DDEVICE pDevice, LPGFX3D_DIRECT3DTEXTURE lpTexture , FLOAT fAlpha, FLOAT& fHeight );
GAMESYSTEM_API void RenderFullScreenTexture(LPGFX3D_DIRECT3DDEVICE pDevice, LPGFX3D_DIRECT3DTEXTURE lpTexture , FLOAT fAlpha );
void TriggerCode::Render(LPGFX3D_DIRECT3DDEVICE pDevice)
{
	if ( m_eState != TriggerCodeState_Sleep && //非睡眠状态
		 m_dwTextID != 0 &&//文本ID有效
		 m_bChackConditionEnable )//满足判定条件
	{
		CStringW tpOutPutStr = Tfx_GetStringW(m_dwTextID);
		D3DCOLOR clrShadow =0xff000000;
		D3DXCOLOR clrText(1.0f ,1.0f ,1.0f ,1.0f);
		CTextRenderAttrib textRenderAttrib;
		textRenderAttrib.m_dwFlags = CTextRenderAttrib::_TRA_SHADOW |CTextRenderAttrib::_TRA_CONTROLCHAR | CTextRenderAttrib::_TRA_MULTILINE|CTextRenderAttrib::_TRA_WORDBREAK;//开启控制字符，以便控制颜色等
		textRenderAttrib.m_cShadowType = CTextRenderAttrib::_SHADOW_TYPE_1;  
		textRenderAttrib.m_clrShadow = clrShadow;
		textRenderAttrib.m_rectClip.left	 = GetModuleMng()->GetClientCx() / 4;
		textRenderAttrib.m_rectClip.right	 = GetModuleMng()->GetClientCx() * 3/4;
		
		int textStartPersent = cfg_Game_iTriggerTextTop_Low;

		if ( GetScene()->GetCourseID() == cfg_Game_bIsTrainYardID )//很龌龊的代码，毛海滨让我这么写的。BY：who
		{
			textStartPersent = cfg_Game_iTriggerTextTop_Heigh;
		}

		textRenderAttrib.m_rectClip.top		 = GetModuleMng()->GetClientCy() * textStartPersent / 100 ;
		textRenderAttrib.m_rectClip.bottom	 = GetModuleMng()->GetClientCy() * ( textStartPersent + 25 ) / 100 ;

		CFontBatchRenderHelper _tempHelp(&textRenderAttrib);
		if ( GetModuleMng()->GetClientCx() < 1280 && GetModuleMng()->GetClientCy() < 800 )
		{
			int strLen = GetUIDriver().GetStringWidth( tpOutPutStr, 0, TRUE, 1 );
			//[2011-04-29][熊嘉琪][英文版提示文本字体变小]
			if (cfg_Game_eLanguage == LT_ENGLISH)
				RenderText(tpOutPutStr ,GetModuleMng()->GetClientCx() / 4 , GetModuleMng()->GetClientCy() * textStartPersent /100 ,clrText,&textRenderAttrib ,0);
			else
				RenderText(tpOutPutStr ,GetModuleMng()->GetClientCx() / 4 , GetModuleMng()->GetClientCy() * textStartPersent /100 ,clrText,&textRenderAttrib ,1);
		}
		else
		{
			int strLen = GetUIDriver().GetStringWidth( tpOutPutStr, 0, TRUE, 2 );
			//[2011-04-29][熊嘉琪][英文版提示文本字体变小]
			if (cfg_Game_eLanguage == LT_ENGLISH)
				RenderText(tpOutPutStr ,GetModuleMng()->GetClientCx() / 4 , GetModuleMng()->GetClientCy() * textStartPersent /100 ,clrText,&textRenderAttrib ,1);
			else
				RenderText(tpOutPutStr ,GetModuleMng()->GetClientCx() / 4 , GetModuleMng()->GetClientCy() * textStartPersent /100 ,clrText,&textRenderAttrib ,2);
		}		
			
	}

	if(m_eState != TriggerCodeState_Sleep && //非睡眠状态
		m_dwPicID != -1 &&//图片ID有效
		m_bChackConditionEnable )//满足判定条件
	{
		if( m_pTexture == NULL )
			m_pTexture = GetUITexMng()->QueryTexture( m_dwPicID );
		else
		{
			if( m_ePicturePos == TriggerElement_Picture::ElementState_Sound_FullScreen)
			{//全屏拉伸
				RenderFullScreenTexture(pDevice,m_pTexture->GetD3DTexture(),0.0f);
			}
			else if( m_ePicturePos == TriggerElement_Picture::ElementState_Sound_Middle)
			{//居中
				RenderMiddleScreenTexture(pDevice,m_pTexture->GetD3DTexture(),0.0f);
			}
			else if( m_ePicturePos == TriggerElement_Picture::ElementState_Sound_Rate)
			{//等比率
				FLOAT fHeight(0.f);
				RenderRateTexture(pDevice,m_pTexture->GetD3DTexture(),0.0f,fHeight);
			}
		}
	}

	if( cfg_Graphic_bRenderTriggerDebug )
	{
		CStringW tpOutPutStr;
		tpOutPutStr.Format(L" %d号触发器状态 = ",m_dwID);
		switch( m_eState )
		{
		case TriggerCodeState_Sleep:
			tpOutPutStr += "休眠";
			break;
		case TriggerCodeState_Prepare:
			tpOutPutStr += "就绪";
			break;
		case TriggerCodeState_Active:
			tpOutPutStr += "激活";
			break;
		}
		GetFontManager()->GetFontRender(0)->DrawText(tpOutPutStr, 200  + ( m_dwID / 30 * 200 ) , 150 + ( m_dwID % 30 * 20 ) ); 
	}
}

//====================================================================
TriggerMng::TriggerMng()
{

}

TriggerMng::~TriggerMng()
{
	Release();
}

// 功能：	序列化函数，实现数据内容的存储与读取
// 参数：	arc - 指定用于序列化的文档
// 注：本函数出现错误时会抛异常CSerializerException出来，所以外面调用函数需要进行处理
void TriggerMng::Serialize(COUArchiveEx& arc)
{
	if ( arc.IsStoring() )
	{
	}
	else
	{
		BYTE bVersion = 0;
		arc >> bVersion;

		DWORD objSize = 0;
		arc >> objSize;

		for(UINT tpCnt = 0; tpCnt < objSize; tpCnt++ )
		{
			TriggerCode* tpCode = new TriggerCode();
			tpCode->Serialize(arc,bVersion);
			m_TriggerCodeArray.push_back( tpCode );
		}
	}
}

//功能：删除指针释放资源
void TriggerMng::Release()
{
	UINT tpCnt;
	for ( tpCnt = 0; tpCnt < m_TriggerCodeArray.size() ; tpCnt++)
	{
		delete m_TriggerCodeArray[tpCnt];
	}
	m_TriggerCodeArray.clear();
}

void TriggerMng::Simulate(FLOAT fElapsedTime)
{
	UINT tpCnt;
	for ( tpCnt = 0; tpCnt < m_TriggerCodeArray.size() ; tpCnt++)
	{
		m_TriggerCodeArray[tpCnt]->Simulate(fElapsedTime);
	}

	m_TriggerEventArray.clear();
}

void TriggerMng::Render(LPGFX3D_DIRECT3DDEVICE pDevice)
{
	UINT tpCnt;
	for ( tpCnt = 0; tpCnt < m_TriggerCodeArray.size() ; tpCnt++)
	{
		m_TriggerCodeArray[tpCnt]->Render(pDevice);
	}
}

void TriggerMng::SetTriggerState(std::vector<TriggerCodeState> tmpTriggerState)
{
	if(tmpTriggerState.empty())
		return ;
	for(int nIndex = 0; nIndex < tmpTriggerState.size(); nIndex ++)
	{
		m_TriggerCodeArray[nIndex]->SetState(tmpTriggerState[nIndex]);
	}
}

TriggerCode* TriggerMng::FindTrigger(DWORD id)
{
	UINT tpCnt;
	for ( tpCnt = 0; tpCnt < m_TriggerCodeArray.size() ; tpCnt++)
	{
		if ( m_TriggerCodeArray[tpCnt]->GetID() == id )
		{
			return m_TriggerCodeArray[tpCnt];
		}
	}
	return NULL;
}

void TriggerMng::AddTriggerEvent(TriggerEventCode& triggerEvent)
{
	//目前只记录本地玩家发起的事件
	if( triggerEvent.m_dwAttackerCRID == GetLocalPlayer()->GetCRID())
	{
		m_TriggerEventArray.push_back(triggerEvent);
	}
}

BOOL TriggerMng::IfHappenTriggerEvent(TriggerEvent eTriggerEvent)
{
	for(int nIndex =0; nIndex < (int)m_TriggerEventArray.size(); nIndex ++)
	{
		if( m_TriggerEventArray[nIndex].m_TriggerEventType == eTriggerEvent)
			return TRUE;
	}
	return FALSE;
}