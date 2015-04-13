![battle-logo-2352021284-6_avatar.png](https://bitbucket.org/repo/8nLMMg/images/3289218395-battle-logo-2352021284-6_avatar.png)...:: BattleCore ::...



Introduction


    Copyright (C) TrinityCore (https://github.com/TrinityCore/TrinityCore)
    Copyright (C) BattleCore (https://bitbucket.org/Vitup/battlecore)

Ядро основано на разработках коммьюнити Trinity Core - http://trinitycore.org/ следовательно, выражаю благодарность всем тем людям, которые приложили свои умения к его развитию.

Порядок заливки базы мира:

    Ядро оптимизировано под базу TDB .
    Чтобы собрать базу нужно взять эту версию, залить на нее файлы из папки sql/update/.
    Потом нужно залить файлы в таком порядке:
    In auth: auth_FULL.sql
    In char: characters_FULL.sql
    In world: world_FULL.sql => world_update.sql



Requirements

    Platform: Linux, Windows or Mac
    Processor with SSE2 support
    ACE >= 5.8.3
    MySQL >= 5.1.0
    CMake >= 2.8.0
    OpenSSL >= 0.9.8o
    GCC >= 4.3 (Linux only)
    MS Visual Studio >= 9 (2008) (Windows only)


Authors, Contributors

    Admin dev: Vitup
    Dev's: Willian
    Dev's: Lighto

