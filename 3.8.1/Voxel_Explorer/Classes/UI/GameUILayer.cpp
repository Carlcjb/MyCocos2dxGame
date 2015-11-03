//
//  GameUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/16.
//
//

#include "GameUILayer.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
#include "PopupUILayerManager.h"
#include "PlayerProperty.hpp"
#include "GameFormula.hpp"
#include "VoxelExplorer.h"
USING_NS_CC;
GameUILayer::GameUILayer()
{
    m_pRoleBtn          = nullptr;
    m_pRoleHpBar        = nullptr;
    m_pRoleCurHp        = nullptr;
    m_pRoleMaxHp        = nullptr;
    m_pRoleMpBar        = nullptr;
    m_pRoleCurMp        = nullptr;
    m_pRoleMaxMp        = nullptr;
    m_pRoleExpBar       = nullptr;
    m_pRoleLevel        = nullptr;
    m_pMonsterLayout    = nullptr;
    m_pMonsterCurHp     = nullptr;
    m_pMonsterMaxHp     = nullptr;
    m_pMonsterLevel     = nullptr;
    m_pMonsterName      = nullptr;
    
    m_pGameMapBtn       = nullptr;
    m_pGameMsgBtn       = nullptr;
    m_pGameSearchBtn    = nullptr;
    
    for (int i = 1 ; i<9; i++) {
        m_pRoleBuffers[i] = nullptr;
        m_pMonsterBuffers[i] = nullptr;
    }
    
    _isOpenSmailMap = false;
    
}
GameUILayer::~GameUILayer()
{
    
}
bool GameUILayer::addEvents()
{
      
    m_pRoleBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "btn_role"));
    if (!m_pRoleBtn)
        return false;
     m_pRoleHpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood"));
    if (!m_pRoleHpBar)
        return false;
    m_pRoleMpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic"));
    if (!m_pRoleMpBar)
        return false;

    m_pRoleCurHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood_num"));
    if (!m_pRoleCurHp)
        return false;

    m_pRoleMaxHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood_maxnum"));
    if(!m_pRoleMaxHp)
        return false;

    m_pRoleCurMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic_num"));
    if (!m_pRoleCurMp)
        return false;

    
    m_pRoleMaxMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic_maxnum"));
    if(!m_pRoleMaxMp)
        return false;

    
    m_pRoleExpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_exp"));
    if(!m_pRoleExpBar)
        return false;

    
    m_pRoleLevel = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_lv_num"));
    if (!m_pRoleLevel)
        return false;
    
    for (int i=1 ; i<9; i++)
    {
        m_pRoleBuffers[i] =  dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, StringUtils::format("role_buffer_%d",i)));
        if(!m_pRoleBuffers[i])
            return false;
        m_pRoleBuffers[i]->setVisible(false);
    }
    
    
    m_pMonsterLayout =  dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "Panel_monster"));
    if (!m_pMonsterLayout)
        return false;

    m_pMonsterCurHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_monster_blood_num"));
    if (!m_pMonsterCurHp)
        return false;
    
    
    m_pMonsterMaxHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_monster_blood_maxnum"));
    if(!m_pMonsterMaxHp)
        return false;
   
    
    m_pMonsterLevel = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "monster_lv_num"));
    if (!m_pMonsterLevel)
        return false;
   
    
    for (int i=1 ; i<9; i++)
    {
        m_pMonsterBuffers[i] =  dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, StringUtils::format("monster_buffer_%d",i)));
        if(!m_pMonsterBuffers[i])
            return false;
        m_pMonsterBuffers[i]->setVisible(false);
    }

    m_pGameMsgBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_msg"));
    if (!m_pGameMsgBtn)
        return false;
    m_pGameMapBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_map"));
    if (!m_pGameMapBtn)
        return false;
    m_pGameSearchBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_search"));
    if (!m_pGameSearchBtn)
        return false;
    m_pGameMapBtn->setTouchEnabled(true);
    m_pGameMapBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickMap, this));

    m_pGameSearchBtn->setTouchEnabled(true);
    m_pGameSearchBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickSearch, this));
    m_pGameMsgBtn->setTouchEnabled(true);
    m_pGameMsgBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickMsg, this));

    
    
    m_pRoleBtn->setTouchEnabled(true);
    m_pRoleBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickRole, this));
    m_pRoleHpBar->setScale9Enabled(true);
    float hpPer =PlayerProperty::getInstance()->getCurrentHp().GetFloatValue()/PlayerProperty::getInstance()->getMaxHp().GetFloatValue() *100.0f;
    m_pRoleHpBar->setPercent(hpPer);
    float mpPer =PlayerProperty::getInstance()->getCurrentMp().GetFloatValue()/PlayerProperty::getInstance()->getMaxMp().GetFloatValue() *100.0f;
    m_pRoleMpBar->setScale9Enabled(true);
    m_pRoleMpBar->setPercent(mpPer);
    m_pRoleCurHp->setString(Value(int(PlayerProperty::getInstance()->getCurrentHp())).asString());
    m_pRoleMaxHp->setString(Value(int(PlayerProperty::getInstance()->getMaxHp())).asString());
    m_pRoleCurMp->setString(Value(int(PlayerProperty::getInstance()->getCurrentHp())).asString());
    m_pRoleMaxMp->setString(Value(int(PlayerProperty::getInstance()->getMaxHp())).asString());
    float ExpPer =PlayerProperty::getInstance()->getExp().GetLongValue()/GameFormula::getNextLevelExp(PlayerProperty::getInstance()->getLevel()) *100.0f;
    CCLOG("EXPPER:%f",ExpPer);
    m_pRoleExpBar->setScale9Enabled(true);
    m_pRoleExpBar->setPercent(ExpPer);
    m_pRoleLevel->setString(Value(int(PlayerProperty::getInstance()->getLevel())).asString());
    m_pMonsterLayout->setVisible(false);
    m_pMonsterCurHp->setString("");
    m_pMonsterMaxHp->setString("");
    m_pMonsterLevel->setString(Value(int(PlayerProperty::getInstance()->getLevel())).asString());

    
    
    return true;
}
void GameUILayer::onClickRole(Ref* ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickRole");
    PopupUILayerManager::getInstance()->openPopup(ePopupRole);
}
void GameUILayer::onClickMap(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMap");
    if (_isOpenSmailMap) {
        VoxelExplorer::getInstance()->getCurrentLevel()->showMap(false);
        _isOpenSmailMap = false;
    }else{
        VoxelExplorer::getInstance()->getCurrentLevel()->showMap(true);
         _isOpenSmailMap = true;
    }
    
    
}
void GameUILayer::onClickMsg(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMsg");
}
void GameUILayer::onClickSearch(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickSearch");
}
void GameUILayer::onEventLevelUp(cocos2d::EventCustom *sender)
{
    
}