#include "RenderCanvas.h"
//#include "RenderCanvasTest.h"

//int main()
//{
//	return 0;
//}

//int main()
//{
//	RenderCanvasTest* app = new RenderCanvasTest();
//	app->OnInit();
//	app->RenderLoop();
//
//	return EXIT_SUCCESS;
//}


/*-
* Copyright ? Gerallt Franke 2017.
* All rights reserved.
* Description: Athena Engine.
* Date: 18/05/2017
* Licence: For the purpose of educational use only.
*          All rights reserved to the author.
* Abstract: The Athena Engine.
*
*                                      '
*    [ ATHENA V1.17 ]           . ` ;  ::
*                              , : +:;,,@
*                            '#:. '#` + @;
*            ;               :+:,.@#;'.; +,
*            `               '+;.'@'+@@ :@+
*           @              '+;;'+@@'@@' +@'@
*           @              :'::##@+##':@#@@''
*         +:+              #::;;@@,;@@+@##;@@:
*        @'##            ` +;###@#@''#.@@###@@+
*        '#@@            .`@+@#;+@';@@#+@'##@@@++
*       #@@@@            ++@++;;@':+;+:;@+++#@@+#+'
*       #@@@@#          ##@++#++:'+';@#@#:'';+@#;#;@
*      '@@ @@@,        #+#;@#@##;+.,@#@+@+;;''#@#;@+@
*      @#@@@@@#      `;@#@##@+##;#@,#@#@#@;:;;:+@@:@;#,
*      #@@@@@@@#    :'#,:+#'#++@#+#+;@@@@@;''::;'@#+,#'+
*     ,#@@@@@@@@@   ;'+@@;'#@+@#@@@@#+'@@@@;@@##::@;@;,'+
*     @#@@@@@@@@@@  :`+@###+;@';@'+;.`'@@@@@@@#@#@:@,@;:++
*    #@@@@@@@@@@@@@ #@;@#@@+'@'@+#@@@+@@@@@#@'@@#@@;@;@';@'
*    @@@@@    @@@@@@@++++@+'@@@@@@@#@@;+@@@###+@@@@@'#;+;'#@
*   +@@@@@@@@@@@@@@@#+@@@+@+;+@@,+@`@:+@@@###@+` @@@@#';+#;@;
*   @@@@@@@@@@@@@@@@@@;#'##+###@@#+@@@@'@@##@@@@      @';;@'#
*   @#@@@@@@@#@@@@@#@+#@+@#@;@@        @@@##@@@#@     ,@:;'@;+
*  #@#@@@@@@@     +@@:#++#+@@@@@#@@@@@@@@@@@@@@@@     ;#@:;'@#+
*  @##@@@@@#       @@@@+#+##'@@@@@++@@#@@@@@@@@@###;   @#@;''#@,
*  @@@@@@@@        '@##'#@;#@@@@@@@@@@@@@@@   @@@@#+`  @@'@;'';@'
* ,@@ @@@,         @#+#@''',#@@@@@@@@@@@@@@@@@@@@@#@#' `@@'@'+''@++;
* @##@@@@          .@##+#+#;@@@@@@@@#@@@@@@#@@@#@@@@+@. @  ;''++'#'++
* @@@@@#           `#@#'+++`,+@@@@@#@@  +. #@@#  @@@##@ @   ;''.`'#+#+
* @@@@'             #@+@+:+`` @@@#@+`      @@@+    @@#++    ,@'+ @'++#
*'@@@@              #@##@#+# #@@@@         @@@'     @@@@'    '@++ '+##+
*@@@                @@@;@#'+,#@@+          @@@.      #@@@     '+'#+;++@'
*@@;                '@#@##'#'@ @           @@@        @@+      '''@'+++#:
*@@;                 ###@@@,#.             +#@        .@#,     ,''#''+++'
*@@                  `'@@'#@#.   ,         ###`        @++      ##' .;++#
*@@                +  :@@#+@,@+  ,     '   @@#+        ;#@:      '+   ++##
*@                  '  ++@.''::; '@   ;    ##@@:        #@:       +;   '++
*@                  `;   @;@#+' #@;  :     @##@+        @#'     +  +    '+
*                    +'; :@'':: +'  #+     +##@@:       @:+        +     +'
*                     @''#';@+++: ,.@      #@@@@+       ##'         .    :#
*                      `@+ `';;+@' ;,       @#@@#@       '+               +
*                       @@@ ',,+# @`        @@#@@#       @;               ,:
*                         #;+.'':,          @@#,@@;      @+                #
*                         :@#+.''`           @# @@@      @#                .
*                         '@#''#;             @ @@#      @+                 `
*                          @#@@#;             @:`@#      @#
*                           @@@+              @: @#      #+
*                            ''               @; '#      '+
*                            ,,               @. ,@      .++
*                            `                @`  @      .@
*                                             +   @       @
*                                                 .        '
**********************************************************  +  */

#include "GameSystem.h"
#include "testing.h"

#define SYS_DATABASE "Game.ini"

//Athena Application Entry Point
int main(int argc, char **argv, char **envp)
{
	//QApplication	App(argc, argv);
	// .---------------------------------------------.
	// .--------------- ATHENA ENGINE----------------.

	// Parse game startup options, variables, and ini database configuration.
	GameConfig SystemConfig;

	//GameSystem::ConsoleSubsystem();
	GameSystem::ParseEnvVariables(SystemConfig, envp);
	GameSystem::ParseArgs(argc, argv, SystemConfig);
	GameSystem::ParseSysDatabase(SystemConfig, SYS_DATABASE);


	// -................. base system ..................-

	if (SystemConfig.IsEnabled(GameStartupOption::HIDE_ERRORS))
	{
		// Disable underlying console buffer.
		std::streambuf* rd_buf = std::cout.rdbuf();
		std::cout.rdbuf(NULL);
	}

	if (SystemConfig.IsEnabled(GameStartupOption::UNIT_TESTING))
	{
		// Quick Tests.
		athena_quick_tests();

		if (SystemConfig.IsEnabled(GameStartupOption::UNIT_TESTING_ONLY))
			return 0;
	}

	// .---------------------------------------------.
	// Initilise Engine Application.
	// -.............................................-

GameInitilisation: int code = GameSystem::ApplicationLoader(&SystemConfig);

	if (SystemConfig.RestartApplication)
	{
		SystemConfig.RestartApplication = false;
		goto GameInitilisation; // worst idea ever
	}

	return code;
}
