#include "ScriptPCH.h"
#include "Channel.h"

class System_Censure : public PlayerScript
{
    public:
        System_Censure() : PlayerScript("System_Censure") {}

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg)
        {
            CheckMessage(player, msg, lang, NULL, NULL, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver)
        {
            CheckMessage(player, msg, lang, receiver, NULL, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* group)
        {
            CheckMessage(player, msg, lang, NULL, group, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* guild)
        {
            CheckMessage(player, msg, lang, NULL, NULL, guild, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel)
        {
            CheckMessage(player, msg, lang, NULL, NULL, NULL, channel);
        }

    void CheckMessage(Player* player, std::string& msg, uint32 lang, Player* /*receiver*/, Group* /*group*/, Guild* /*guild*/, Channel* channel)
    {
        if (player->IsGameMaster() || lang == LANG_ADDON)
            return;

        // transform to lowercase (for simpler checking)
        std::string lower = msg;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        // Переписать, если уж будем это использовать
        const uint8 cheksSize = 51;
        std::string checks[cheksSize];
        // Strony (Sites)
        checks[0] ="http://";
        checks[1] =".com";
        checks[2] =".www";
        checks[3] =".net";
        checks[4] =".org";
        checks[5] =".ru";
        checks[6] ="www.";
        checks[7] ="wow-";
        checks[8] ="-wow";
        checks[9] =".pl";
        checks[10] ="wowgear";
        checks[11] ="wоwgеаr";
        checks[12] ="мs";
        checks[13] ="-ms";
        checks[14] ="easy-";
        checks[15] ="-easy";
        checks[16] ="еаsy";
        checks[17] ="easу";
        checks[18] ="project";
        checks[19] ="prоjеct";
        checks[20] ="prоjеct";
        checks[21] ="-rasta";
        checks[22] ="rasta";
        checks[23] ="rasta-";
        checks[24] ="rаsta";
        checks[25] ="gеаr";
        checks[26] ="deluxe";
        checks[27] ="deluxe-";
        checks[28] ="-deluxe";
        checks[29] ="вовгир";
        checks[30] ="biz";
        checks[31] =".biz";
        checks[32] =".ру";
        checks[33] =".рф";
        checks[34] =".b/i/z";
        checks[35] =".биз";
        checks[36] =".биз";
        checks[37] =".биз";
        checks[38] =".биз";
        checks[39] ="wowflag";
        checks[40] ="wоwflag";
        checks[41] ="-lion";
        checks[42] ="lion-";
        checks[43] ="-liоn";
        checks[44] ="lion";
        checks[45] ="liоn";
        checks[46] ="www";
        checks[47] ="Приглашаю на";
        checks[48] ="Заходи на";
        checks[49] ="Приглашаю на";
        checks[50] ="Заходи на";

        for (int i = 0; i < cheksSize; ++i)
            if (lower.find(checks[i]) != std::string::npos)
            {
                msg = "";
                ChatHandler(player->GetSession()).PSendSysMessage("Система зафиксировала возможную попытку создать спам-сообщение.");
                return;
            }
    }
};

void AddSC_System_Censure()
{
    new System_Censure();
}
