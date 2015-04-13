#include "ScriptMgr.h"
#include "Player.h"

class SystemAwardsForTime : public PlayerScript
{
public:
	SystemAwardsForTime() : PlayerScript("SystemAwardsForTime") { }

	// extract items for mail
	typedef std::pair<uint32, uint32> ItemPair;
	typedef std::list< ItemPair > ItemPairs;
	ItemPairs mailItems;

	void SendMail(Player* player, std::string subject, std::string text, uint32 money = 0)
	{
		if (mailItems.size() > MAX_MAIL_ITEMS)
			return;

		// from console show not existed sender
		MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

		// fill mail
		MailDraft draft(subject, text);

		SQLTransaction trans = CharacterDatabase.BeginTransaction();

		for (ItemPairs::const_iterator itr = mailItems.begin(); itr != mailItems.end(); ++itr)
        {
            if (Item* item = Item::CreateItem(itr->first, itr->second))
            {
                item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                draft.AddItem(item);
            }
        }

		if (money != 0)
			draft.AddMoney(money);
		draft.SendMailTo(trans, MailReceiver(player, player->GetGUID()), sender);
		CharacterDatabase.CommitTransaction(trans);
		mailItems.clear();
	}
	
	void OnTime(Player* player, uint32 total, uint32 /*level*/)
	{
		if (!sWorld->getBoolConfig(CONFIG_AWARDS_PER_TIME))
			return;
			
		switch (total)
		{
			case 7200: // 2 hours
				player->ModifyMoney(5000000);
				ChatHandler(player->GetSession()).SendSysMessage("Сообщение");
				break;
			case 14400: // 4 hours
				player->AddItem(49426, 35);
				ChatHandler(player->GetSession()).SendSysMessage("Сообщение");
				break;
			case 28800: // 8 hours
				player->ModifyHonorPoints(500); // 500 Honor Points
				player->ModifyArenaPoints(250); // 250 arena points
				ChatHandler(player->GetSession()).SendSysMessage("Сообщение");
				break;
			case 57600: // 16 hours
				// Максимум 12 вещей!
				// mailItems.push_back(ItemPair(Ид вещи, кол-во));
				mailItems.push_back(ItemPair(5133, 3));
				SendMail(player, "Заголовок письма", "Содержание письма");
				ChatHandler(player->GetSession()).SendSysMessage("Сообщение");
				break;
			case 115200: // 32 hours
				mailItems.push_back(ItemPair(5133, 1));
				mailItems.push_back(ItemPair(5133, 3));
				mailItems.push_back(ItemPair(5133, 5));
				SendMail(player, "Заголовок письма", "Содержание письма", 5000000); // Send Items +500 gold
				ChatHandler(player->GetSession()).SendSysMessage("Сообщение");
				break;
			default:
				break;
		}
	}
};

void AddSC_AwardsForTime() 
{		
	new SystemAwardsForTime();
}