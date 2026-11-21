/* Keyboard strings for the EU 1.00 English UI. The guest owns the original controller strings. */
typedef struct { const char *key, *text; uint32_t address; } PcPrompt;
static PcPrompt pc_prompts[] = {
    {"UI_CONTROL_ANALOGSTICK_L", "W A S D - Move"},
    {"UI_CONTROL_ANALOGSTICK_R", "Mouse - Look"},
    {"UI_CONTROL_BUTTON_CIRCLE", "C - Crouch / Ctrl - Prone"},
    {"UI_CONTROL_BUTTON_SELECT", "Tab - Scoreboard"},
    {"UI_CONTROL_BUTTON_SQUARE", "F - Use / R - Reload"},
    {"UI_CONTROL_BUTTON_START", "Esc - Pause"},
    {"UI_CONTROL_BUTTON_TRIANGLE", "1 / 2 / Wheel - Switch"},
    {"UI_CONTROL_BUTTON_X", "Space - Stand / Jump"},
    {"UI_CONTROL_DPAD_DOWN", "Shift - Sprint"},
    {"UI_CONTROL_TRIGGER_L", "Right mouse - Aim"},
    {"UI_CONTROL_TRIGGER_R", "Left mouse - Fire"},
    {"UI_DESCRIP_TUTORIAL", "Play the first Time Trial to practice movement, aiming and equipment with the keyboard and mouse."},
    {"UI_DIALOG_LABEL_ACCEPT", "Accept"},
    {"UI_DIALOG_LABEL_ACCEPT2", "Accept"},
    {"UI_DIALOG_LABEL_CANCEL", "Cancel"},
    {"UI_DIALOG_LABEL_CANCEL2", "Cancel"},
    {"UI_DIALOG_LABEL_NO", "No"},
    {"UI_DIALOG_LABEL_NO2", "No"},
    {"UI_DIALOG_LABEL_OK", "OK"},
    {"UI_DIALOG_LABEL_OK2", "OK"},
    {"UI_DIALOG_LABEL_YES", "Yes"},
    {"UI_DIALOG_LABEL_YES2", "Yes"},
    {"UI_HEADER_BUTTONLAYOUT", "Keyboard and mouse"},
    {"UI_HUD_NOTIFY_RELOAD", "R - RELOAD"},
    {"UI_HUD_RELOADREMINDER", "R - RELOAD"},
    {"UI_HUD_THROWBACKGRENADE", "Press G or middle mouse to throw back!"},
    {"UI_HUD_WEP_POW_AR_00", "Hold F for M16"},
    {"UI_HUD_WEP_POW_AR_00_CUS", "Hold F for M16 %a"},
    {"UI_HUD_WEP_POW_AR_01", "Hold F for M14"},
    {"UI_HUD_WEP_POW_AR_01_CUS", "Hold F for M14 %a"},
    {"UI_HUD_WEP_POW_AR_02", "Hold F for FAMAS"},
    {"UI_HUD_WEP_POW_AR_02_CUS", "Hold F for FAMAS %a"},
    {"UI_HUD_WEP_POW_AR_03", "Hold F for GALIL"},
    {"UI_HUD_WEP_POW_AR_03_CUS", "Hold F for GALIL %a"},
    {"UI_HUD_WEP_POW_AR_04", "Hold F for AK-47"},
    {"UI_HUD_WEP_POW_AR_04_CUS", "Hold F for AK-47 %a"},
    {"UI_HUD_WEP_POW_AR_05", "Hold F for CARBINE"},
    {"UI_HUD_WEP_POW_AR_05_CUS", "Hold F for CARBINE %a"},
    {"UI_HUD_WEP_POW_BETTY_00", "Hold F to pick up Bouncing Betty"},
    {"UI_HUD_WEP_POW_GENERIC", "Hold F to pick up"},
    {"UI_HUD_WEP_POW_LAUNCH_00", "Hold F for RPG"},
    {"UI_HUD_WEP_POW_LAUNCH_02", "Hold F for STRELA-3"},
    {"UI_HUD_WEP_POW_LAUNCH_03", "Hold F for CHINA LAKE"},
    {"UI_HUD_WEP_POW_LMG_01", "Hold F for RPK"},
    {"UI_HUD_WEP_POW_LMG_01_CUS", "Hold F for RPK %a"},
    {"UI_HUD_WEP_POW_LMG_02", "Hold F for M60"},
    {"UI_HUD_WEP_POW_LMG_02_CUS", "Hold F for M60 %a"},
    {"UI_HUD_WEP_POW_LMG_03", "Hold F for STONER63"},
    {"UI_HUD_WEP_POW_LMG_03_CUS", "Hold F for STONER63 %a"},
    {"UI_HUD_WEP_POW_PISTOL_00", "Hold F for ASP"},
    {"UI_HUD_WEP_POW_PISTOL_00_CUS", "Hold F for ASP %a"},
    {"UI_HUD_WEP_POW_PISTOL_01", "Hold F for SKORPION"},
    {"UI_HUD_WEP_POW_PISTOL_01_CUS", "Hold F for SKORPION %a"},
    {"UI_HUD_WEP_POW_PISTOL_02", "Hold F for .357 MAGNUM"},
    {"UI_HUD_WEP_POW_PISTOL_02_CUS", "Hold F for .357 MAGNUM %a"},
    {"UI_HUD_WEP_POW_PISTOL_03", "Hold F for CZ75"},
    {"UI_HUD_WEP_POW_PISTOL_03_CUS", "Hold F for CZ75 %a"},
    {"UI_HUD_WEP_POW_PISTOL_04", "Hold F for MAC11"},
    {"UI_HUD_WEP_POW_PISTOL_04_CUS", "Hold F for MAC11 %a"},
    {"UI_HUD_WEP_POW_SENTRY_00", "Hold F to pick up Sentry Gun"},
    {"UI_HUD_WEP_POW_SHOTGUN_01", "Hold F for STAKEOUT"},
    {"UI_HUD_WEP_POW_SHOTGUN_01_CUS", "Hold F for STAKEOUT %a"},
    {"UI_HUD_WEP_POW_SHOTGUN_02", "Hold F for SPAS-12"},
    {"UI_HUD_WEP_POW_SHOTGUN_02_CUS", "Hold F for SPAS-12 %a"},
    {"UI_HUD_WEP_POW_SHOTGUN_03", "Hold F for STRIKER"},
    {"UI_HUD_WEP_POW_SHOTGUN_03_CUS", "Hold F for STRIKER %a"},
    {"UI_HUD_WEP_POW_SMG_00", "Hold F for MP5K"},
    {"UI_HUD_WEP_POW_SMG_00_CUS", "Hold F for MP5K %a"},
    {"UI_HUD_WEP_POW_SMG_01", "Hold F for PP-90M1"},
    {"UI_HUD_WEP_POW_SMG_01_CUS", "Hold F for PP-90M1 %a"},
    {"UI_HUD_WEP_POW_SMG_02", "Hold F for AK74U"},
    {"UI_HUD_WEP_POW_SMG_02_CUS", "Hold F for AK74U %a"},
    {"UI_HUD_WEP_POW_SMG_03", "Hold F for UZI"},
    {"UI_HUD_WEP_POW_SMG_03_CUS", "Hold F for UZI %a"},
    {"UI_HUD_WEP_POW_SNIPER_00", "Hold F for DRAGUNOV"},
    {"UI_HUD_WEP_POW_SNIPER_00_CUS", "Hold F for DRAGUNOV %a"},
    {"UI_HUD_WEP_POW_SNIPER_02", "Hold F for L96A1"},
    {"UI_HUD_WEP_POW_SNIPER_02_CUS", "Hold F for L96A1 %a"},
    {"UI_HUD_WEP_POW_SPECIAL_00", "Hold F for CROSSBOW"},
    {"UI_HUD_WEP_POW_SPECIAL_01", "Hold F for EXPLOSIVE VEST"},
    {"UI_HUD_WEP_POW_SPECIAL_02", "Hold F for BALLISTIC KNIFE"},
    {"UI_LABEL_BUTTONLAYOUT", "Keyboard and mouse"},
    {"UI_LOADINGTIP_03", "Press G or middle mouse for a frag grenade. Press 4 for special equipment."},
    {"UI_LOADINGTIP_04", "Press V to melee."},
    {"UI_LOADINGTIP_05", "Press Right Arrow to activate a killstreak."},
    {"UI_LOADINGTIP_06", "Hold Shift while aiming a sniper rifle to steady the scope."},
    {"UI_NAVHELP_BUTTONS", "Keyboard controls"},
    {"UI_NAVHELP_COVERFLOW_BUTONS", "Click to select / Esc to go back"},
    {"UI_NAVHELP_COVERFLOW_TOUCH", "Click to select / Esc to go back"},
    {"UI_NAVHELP_LIST_BUTTONS", "Click to select / Esc to go back"},
    {"UI_NAVHELP_LIST_SCROLL_BUTTONS", "Click to select / Esc to go back"},
    {"UI_NAVHELP_LIST_SCROLL_TOUCH", "Click to select / Esc to go back"},
    {"UI_NAVHELP_LIST_TOUCH", "Click to select / Esc to go back"},
    {"UI_NAVHELP_MAIN_BUTONS", "Click to select"},
    {"UI_NAVHELP_MAIN_TOUCH", "Click to select"},
    {"UI_NAVHELP_OPTIONS_BUTONS", "Arrows to change / Esc to go back"},
    {"UI_NAVHELP_OPTIONS_TOUCH", "Click or drag to select"},
    {"UI_NAVHELP_PAUSE_MP_BUTONS", "Click to select / Esc to go back"},
    {"UI_NAVHELP_PAUSE_MP_TOUCH", "Click to select / Esc to go back"},
    {"UI_NAVHELP_PAUSE_SP_BUTONS", "Click to select / Esc to go back"},
    {"UI_NAVHELP_PAUSE_SP_TOUCH", "Click to select / Esc to go back"},
    {"UI_NAVHELP_TOUCH", "Mouse controls"},
    {"UI_PROMPT_BREACH", "Hold F to breach"},
    {"UI_PROMPT_CARE_AMMO", "Hold F to resupply ammo"},
    {"UI_PROMPT_CARE_ATTACK", "Hold F for Attack Helicopter"},
    {"UI_PROMPT_CARE_BLACKBIRD", "Hold F for Advanced Spy Plane"},
    {"UI_PROMPT_CARE_COUNTER", "Hold F for Counter-Spy Plane"},
    {"UI_PROMPT_CARE_MORTAR", "Hold F for Mortar Strike"},
    {"UI_PROMPT_CARE_SENTRY", "Hold F for Sentry Gun"},
    {"UI_PROMPT_CARE_SPYPLANE", "Hold F for Spy Plane"},
    {"UI_PROMPT_CARE_WEAPON", "Hold F for Weapon"},
    {"UI_PROMPT_COLLECTINTEL", "Hold F to collect intel"},
    {"UI_PROMPT_OPEN", "Hold F to open"},
    {"UI_PROMPT_PICKUPWEAPON", "Hold F for %a"},
    {"UI_PROMPT_PLANTBOMB", "Hold F to plant bomb"},
    {"UI_PROMPT_RELOAD", "R - RELOAD"},
    {"UI_PROMPT_TOMAHAWK", "F to pick up Tomahawk"},
    {"UI_PROMPT_VAULT", "Hold Space to <symbol>"},
    {"UI_TITLESCREEN", "Click to start"},
    {"UI_TUT_BD_BREATH", "Hold Shift to steady your scope<br>Space to continue"},
    {"UI_TUT_BD_BREATHLITE", "Hold Shift to steady your scope"},
    {"UI_TUT_BD_GRENADE", "G or middle mouse - Frag<br>4 - Special grenade<br>Space to continue"},
    {"UI_TUT_BD_GRENADELITE", "G or middle mouse - Frag<br>4 - Special grenade"},
    {"UI_TUT_BD_MELEE", "Press V to melee<br>Space to continue"},
    {"UI_TUT_BD_MELEELITE", "Press V to melee"},
    {"UI_TUT_BD_SPRINT", "Press Shift to sprint with Toggle Sprint enabled<br>Space to continue"},
    {"UI_TUT_BD_SPRINTLITE", "Press Shift to sprint with Toggle Sprint enabled"},
};
static pthread_once_t pc_prompt_once = PTHREAD_ONCE_INIT;
static void pc_prompt_init(void) {
    size_t bytes = 0;
    for (size_t i = 0; i < SDL_arraysize(pc_prompts); ++i)
        bytes += 2 * (strlen(pc_prompts[i].text) + 1);
    uint32_t dst = guest_alloc((uint32_t)bytes, 4);
    if (!dst) return;
    for (size_t i = 0; i < SDL_arraysize(pc_prompts); ++i) {
        pc_prompts[i].address = dst;
        const unsigned char *p = (const unsigned char *)pc_prompts[i].text;
        do { WR16(dst, (uint16_t)*p); dst += 2; } while (*p++);
    }
}
/* At the common return of the game's NLS lookup r5 is the original ASCII key
   and r0 holds its resolved UTF-16 string. Preserve the original on a miss. */
void recomp_ihook_pc_prompt(Cpu *c, int reg) {
    (void)reg;
    if (!c->r[0] || !c->r[5]) return;
    const char *key = (const char *)G(c->r[5]);
    if (SDL_strncasecmp(key, "UI_", 3)) return;
    if (!SDL_strncasecmp(key, "UI_HEADER_", 10)) {
        if (!SDL_strcasecmp(key, "UI_HEADER_BUTTONLAYOUT"))
            __atomic_store_n(&layout_screen,1,__ATOMIC_RELEASE);
        else if (!SDL_strcasecmp(key, "UI_HEADER_GAMEPAUSED") || !SDL_strcasecmp(key, "UI_HEADER_OPTIONS"))
            __atomic_store_n(&layout_screen,0,__ATOMIC_RELEASE);
    }
    if (!window_kbm_active()) return;
    size_t lo = 0, hi = SDL_arraysize(pc_prompts);
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        int order = SDL_strcasecmp(key, pc_prompts[mid].key);
        if (order < 0) hi = mid;
        else if (order > 0) lo = mid + 1;
        else {
            pthread_once(&pc_prompt_once, pc_prompt_init);
            if (pc_prompts[mid].address) c->r[0] = pc_prompts[mid].address;
            break;
        }
    }
}
