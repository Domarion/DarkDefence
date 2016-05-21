#include "Tower.h"



void Tower::connectMethod(std::function<void (Tower *, int, int)> method)
{
    connectedMethod = method;
}

bool Tower::onClick(SDL_Point *point)
{
    if (SDL_PointInRect(point, &getSprite()->getRect()))
    {
        if (connectedMethod != nullptr)
        {
            connectedMethod(this, point->x, point->y);
        }
        return true;
    }
    return false;
}

Tower::Tower(MobModel *model)
    :Mob(model)
{

}

Tower::~Tower()
{

}



/*oid TowerEventListener(GameObject sender,string capt)
    {

        try
        {



        if (waitfordecision == false)
        {
            TowerToUpgrade = sender;
            TowerToUpgradeCapt = capt;
            waitfordecision = true;
            Vector3 screenpos = Camera.main.WorldToScreenPoint(TowerToUpgrade.transform.position);

            towerupController.ControlRect = RelativeScreen.RelativeRect(screenpos.x, RelativeScreen.NativeScreenHeight -screenpos.y, RelativeScreen.getNativeX(towerupController.ControlRect.width), RelativeScreen.getNativeY(towerupController.ControlRect.height));
            towerupController.ClearView();
            towerupController.FillView(GlobalGameVariables.TowerTree.NodeFromName(TowerToUpgradeCapt, GlobalGameVariables.TowerTree.GetRoot()));

            gm.AddGUIControl(towerupController.getavaliableUpgradesView());
            towerupController.RegisterHandler(TowerUpgradeLogic);
            TouchDispatcher.Instance.RegisterHandler(towerupController.getavaliableUpgradesView());
        }
        else
        {

            towerupController.UnRegisterHandler(TowerUpgradeLogic);
            gm.RemoveGUIControl(towerupController.getavaliableUpgradesView());
            towerupController.ClearView();
            TouchDispatcher.Instance.UnRegisterHandler(towerupController.getavaliableUpgradesView());
            waitfordecision = false;
        }

        }
        catch (Exception ex)
        {
            Logger.addExceptionLine("TowerEventListener", ex);
            Application.Quit();
        }
    }


    public void OnTowerUpWindowClose()
    {
        waitfordecision = false;
//		gm.RemoveGUIControl(TowerUpWindow);
    //	TouchDispatcher.Instance.UnRegisterHandler(TowerUpWindow);
    }

    public void TowerUpgradeLogic(string upgrade, short[] upgradePrice)
    {
        string s = upgrade;//TowerUpWindow.ButtonsStatusCheck(TowerToUpgradeCapt);
        if (s != null && s!= TowerToUpgradeCapt)
        {



            ResourcesClass.RemoveResources(upgradePrice);

            GameObject towerUped = Resources.Load("prefabs/Towers/"+s, typeof(GameObject))as GameObject;
            if (towerUped == null)
            {
                ////DebugMap.Instance.NewMessage("towerfailed");
                Logger.addLine(InfoTypes.Error,"towerfailed");
                return;
            }
            Vector3 oldpos = TowerToUpgrade.transform.position;
            Quaternion oldrot = TowerToUpgrade.transform.rotation;
            Destroy(TowerToUpgrade);
            Instantiate(towerUped,oldpos,oldrot);
            waitfordecision = false;
            towerupController.UnRegisterHandler(TowerUpgradeLogic);
            gm.RemoveGUIControl(towerupController.getavaliableUpgradesView());
            TouchDispatcher.Instance.UnRegisterHandler(towerupController.getavaliableUpgradesView());
            towerupController.ClearView();
        }
    }*/
