#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Player.h"
class rewarded_player : public PlayerScript
{
public:
	rewarded_player() : PlayerScript("rewarded_player") {}

	void OnLevelChanged(Player* player, uint8 newLevel)
	{
		switch (++newLevel)
		{
		case 10:
			player->AddItem(49426, 6);
			player->ModifyMoney(1000000, true);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 10 уровня. Мы дарим вам 6 Эмблема льда и 100 золотых.Спасибо за то что вы с нами!|r");
			break;
		case 20:
			player->AddItem(49426, 6);
			player->ModifyMoney(1000000, true);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 20 уровня. Мы дарим вам 6 Эмблема льда и 100 залотых.Спасибо за то что вы с нами!|r");
			break;
		case 30:
			player->AddItem(49426, 6);
			player->ModifyMoney(1000000, true);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 30 уровня. Мы дарим вам 6 Эмблема льда и 100 залотых.Спасибо за то что вы с нами!|r");
			break;
		case 40:
			player->AddItem(49426, 6);
			player->ModifyMoney(1000000, true);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 40 уровня. Мы дарим вам 6 Эмблема льда и 100 залотых.Спасибо за то что вы с нами!|r");
			break;
		case 50:
			player->AddItem(49426, 6);
			player->ModifyMoney(1000000, true);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 50 уровня. Мы дарим вам 6 Эмблема льда и 100 залотых.Спасибо за то что вы с нами!|r");
			break;
		case 60:
			player->AddItem(49426, 6);
			player->ModifyMoney(1000000, true);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 60 уровня. Мы дарим вам 6 Эмблема льда и 100 залотых.Спасибо за то что вы с нами!|r");
			break;
		case 70:
			player->AddItem(49426, 6);
			player->ModifyMoney(1000000, true);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 70 уровня. Мы дарим вам 6 Эмблема льда и 100 залотых.Спасибо за то что вы с нами!|r");
			break;
		case 80:
			player->AddItem(49426, 6);
			player->ModifyMoney(1000000, true);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Поздравляем, вы достигли 80 уровня. Мы дарим вам 6 Эмблема льда и 100 залотых.Спасибо за то что вы с нами!|r");
			break;
		}
	}
};

void AddSC_rewarded_player()
{
	new rewarded_player();
}