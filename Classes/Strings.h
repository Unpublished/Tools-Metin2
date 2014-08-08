//PickUp-Bot Defaults
#if defined(PickUpBot)
	const char *sDefMinSleep = "25";
	const int iDefMinSleep = atoi(sDefMinSleep);
#endif

//PickUp-Bot & Switch-Bot Defaults
#if defined(PickUpBot) || defined(SwitchBot)
	const char *sDefSleep = "500";
	const int iDefSleep = atoi(sDefSleep);
#endif

//SpamBot Defaults
#if defined(SpamBot)
	const char *sDefMinSleep = "750";
	const int iDefMinSleep = atoi(sDefMinSleep);
#endif

//InviDropper - GUI
#if defined(InviDropper)
	const char *sInviDropper	= "InviDropper";
	const char *sDroppen		= "Droppen";
#endif

//Spam-Bot - GUI
#if defined(SpamBot)
	const char *Spam_Bot	= "Spam-Bot";
	const char *sSpammen	= "Spammen";
	const char *sSpamText	= "Spam-Text";
	const char *sChatTyp	= "Chat-Typ";
	const char *sAnzahl		= "Anzahl";

	const char *sChatModes[4] = {"Normaler-Chat", "Ruf-Chat", "Gilden-Chat", "Gruppen-Chat"};
#endif

//Switch-Bot - GUI
#if defined(SwitchBot)
char *SwitchBotOptions			= "Optionen";
const char *sSwitchBot			= "Switch-Bot";
const char *SwitchBotFirstCat	= "1. - 5. Bonus";
const char *SwitchBotSecondCat	= "6. && 7. Bonus";
const char *SwitchBotSettingOne = "Einstellung #1";
const char *SwitchBotSettingTwo = "Einstellung #2";

//Switch-Bot - Messages

//Switch-Bot - Boni
const char *Boni[80] =
{
	"Max. TP",
	"Max. MP",
	"Vitalität (VIT)",
	"Intelligenz (INT)",
	"Stärke (STR)",
	"Beweglichkeit (DEX)",
	"Angriffsgeschwindigkeit",
	"Bewegungsgeschwindigkeit",
	"Zaubergeschwindigkeit",
	"TP-Regeneration",
	"MP-Regeneration",
	"Vergiftungschance",
	"Ohnmachtschance",
	"Verlangsamungschance",
	"Kritischer Treffer",
	"Durchbohrender Treffer",
	"Stark gg Halbmenschen",
	"Stark gg Tiere",
	"Stark gg Orks",
	"Stark gg Esoterische",
	"Stark gg Untote",
	"Stark gg Teufel",
	"Schaden v. TP absorbieren",
	"Schaden v. MP absorbieren",
	"Manaraub",
	"MP bei Treffer erhalten",
	"Nahkampf-Ang. abblocken",
	"Pfeilangriff ausweichen",
	"Schwertverteidigung",
	"Zweihänderverteidigung",
	"Dolchverteidigung",
	"Glockenverteidigung",
	"Fächerverteidigung",
	"Pfeilwiederstand",
	"Feuerwiederstand",
	"Blitzwiederstand",
	"Magiewiederstand",
	"Windwiederstand",
	"Nahkampftreffer refl.",
	"Fluch reflektieren",
	"Giftwiederstand",
	"MP wiederherstellen", "EXP-Bonus",
	"Dopp. Menge Yang",
	"Dopp. Menge Gegenstände",
	"Trank Effektzuwachs",
	"TP wiederherstellen",
	"Immun gg Ohnmacht",
	"Immun gg Verlangsamen",
	"Immun gg Stürzen",
	"",
	"Bogenreichweite",
	"Angriffswert",
	"Verteidigung",
	"Magischer Angriffswert",
	"Magische Verteidigung",
	"",
	"Max. Ausdauer",
	"Stark gg Krieger",
	"Stark gg Ninja",
	"Stark gg Sura",
	"Stark gg Schamane",
	"Stark gg Monster",
	"Angriffswert",
	"Verteidigung",
	"EXP", "Dropchance v. Gegenständen",
	"Dropchance v. Yang",
	"",
	"Fertigkeitsschaden		(FKS)",
	"Durchschnittsschaden	(DSS)",
	"Wiederstand gg FKS",
	"Wiederstand gg DSS",
	"",
	"iCafe-EXP-Bonus",
	"iCafe-Gegenstände-Bonus",
	"Abwehr gg Krieger",
	"Abwehr gg Ninja",
	"Abwehr gg Sura",
	"Abwehr gg Schamanen"
};
#endif

//Tools einstellen - GUI
#if defined(ToolsEinstellen)
	const char *sSearchPatterns[2] = {"Suchmuster #1 2010+ (Standart)", "Suchmuster #2 2008- (Hamachi)"};
#endif

//Upp-Tool - GUI
#if defined(UppTool)
	const char *sUppTool = "Upp-Tool";
	//Save strings
	const char *sCountedUpp = "Anzahl Upp-Vorgänge aktiviert";
	const char *sUppCount = "Anzahl Upp-Vorgänge";
	const char *sSegiValue = "Segi Value";
	const char *sMagMetallValue = "Magisches Metall Value";
	const char *sMaxSlotUpp = "Uppen Max Slot aktiviert";
	const char *sUppMaxSlot = "Uppen Max Slot";
#endif
//Message Strings
const char *sErrorGettingWorkingDir		= "Fehler beim Auslesen des Ordner!";
const char *sError						= "Fehler";
const char *sWarning					= "Achtung!";
const char *CloseDialog					= "Möchtest du das Tool (%s) zusammen mit dem Metin2 Prozess wirklich beenden?";


//Button Strings
const char *sStart	= "Starten";
const char *sStop	= "Stoppen";
const char *sSave	= "Speichern";
const char *sReset	= "Zurücksetzen";
const char *sLoad	= "Laden";

//Misc Strings
const char *sConfigFile		= "Konfigurationsdatei";
const char *sExt			= ".ini";
const char *sFont			= "Tahoma";
const char *sSettings		= "Einstellungen";
const char *sSearchPattern	= "Suchmuster";
const char *UserAgent		= "Tools by Unpublished";
#define win_endl			"\r\n"

#if (DbgSession)
	const char *sDbgOutput = "DbgOutput";
	std::string DbgOutput;
#endif