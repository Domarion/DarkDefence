#include "ScoreScene.h"
#include "../Input/InputDispatcher.h"
#include "../GlobalScripts/GameModel.h"
#include <list>
using std::list;
#include <string>
using std::string;

ScoreScene::ScoreScene()
    :arialFont(nullptr)
{

}

ScoreScene::~ScoreScene()
{
    TTF_CloseFont(arialFont);
}

void ScoreScene::initScene(SceneManager *sceneManagerPtr)
{
    if (!wasInited)
    {
        Scene::initScene(sceneManagerPtr);
        arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 18);
        SDL_Color color = {255, 255, 255};
        button.setFont(arialFont, color);
        button.setRect(700, 550, 100, 50);
        button.setText("Главное меню");
        string s = "MainMenu";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s));
        listGUI.push_back(&button);

        ScoreLabel.setFont(arialFont, color);
        ScoreLabel.setRect(0, 0, 300, 400);


        string ScoreText;
        if (GameModel::getInstance()->getGameStatus() == Enums::GameStatuses::gsWON)
        {
            ScoreText = "Получена награда:";
            list<string> missionRewardItems = GameModel::getInstance()->getMissionReward().getFullDescription();
            for(auto mri = missionRewardItems.begin(); mri != missionRewardItems.end(); ++mri)
                ScoreText+= "\n" + *mri;

        }
        else
            ScoreText = "Миссия провалена";

        ScoreLabel.setText(ScoreText);
        listGUI.push_back(&ScoreLabel);
    }
    InputDispatcher::getInstance()->addHandler(&button);
}

/*
 * 	try
        {
        if (GlobalGameVariables.GameStatus == "Won")
        {
            ScoreText.Text = "Получена награда:";
            int goldCoins = 0;
            float x = 0;

            if (GlobalGameVariables.globReward != null)
            {
                List<string> lst = GlobalGameVariables.globReward.ItemNames;

                if (lst != null)
                {
                    Logger.addLine("Score: RewardList not null");

                    ItemListClass.FillInventoryItemList(lst.ToArray());
                    someoneList = new Label[lst.Count];
                    for(int i = 0; i < lst.Count; ++i)
                    {
                            Texture2D itemtexture = ItemListClass.getItemByName(lst[i]).ItemIcon;
                            someoneList[i] = new Label(RelativeScreen.RelativeRect(x, 200, 300, 50), new GUIContent(lst[i], itemtexture));
                            x += RelativeScreen.getNativeX(someoneList[i].ControlRect.xMax);
                            panel.AddGUIControl(someoneList[i]);

                    }
                }
                goldCoins += GlobalGameVariables.globReward.Gems;
                MapMenu.CurrentMapIndex++;
            }

            string ResourceCaption = ResourcesClass.GetResourceNameFromIndex((byte)ResourcesTypes.Gold);
            Texture2D goldtexture = Resources.Load("textures/Resources/" +  ResourceCaption, typeof(Texture2D)) as Texture2D;

            int points = GlobalGameVariables.PointsPerMap;
            goldCoins += Mathf.FloorToInt(points/100.0f);
            AccountInformation.GoldCoins += goldCoins;

            Label someone2 = new Label(RelativeScreen.RelativeRect(x, 0.5f*RelativeScreen.NativeScreenHeight, 300, 50), new GUIContent(goldCoins.ToString(),goldtexture));
            panel.AddGUIControl(someone2);
        }
        else
            ScoreText.Text = "Миссия провалена";

        }catch (System.Exception ex)
        {
            Logger.addExceptionLine("Something wrong with Score", ex);
        }
*/
void ScoreScene::finalizeScene()
{
    TTF_CloseFont(arialFont);
}
