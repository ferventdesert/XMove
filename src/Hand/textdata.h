

#if INPUT_CONTROL_EN==1

struct t9PY_index
{
	const unsigned long  t9PY;
	const unsigned char *PY;
	const unsigned char *PY_mb;
};

struct t9py_struct
{
	unsigned char  pysrf;       //ÊäÈë·¨Ñ¡Ïî
	unsigned char  firstno;     //ÊäÈëµÄµÚÒ»¸öÊı×Ö°´¼ü
	unsigned char  mblen;       //²é³öÂë±íµÄ³¤¶È
	unsigned char  mbtimes;     //Âë±íÇĞ»»µÄ´ÎÊı
	unsigned long t9py;		//Êı×Ö°´¼ü×éºÏ,×éºÏ³É16½øÖÆ£¬±ÈÈç°´¼ü246ÔòÎª0x246
	const struct t9PY_index  *t9PY_addr;
};


const unsigned char t9PY_indexlen[10] = {1,1,55,33,38,57,44,79,19,74};   //ÒÔÃ¿¸öÊı×Ö¼ü¿ªÊ¼µÄÆ´Òô´úÂë×éºÏÊıÁ¿

/*******************************************************************************
**¹¦ÄÜ£ºÆ´ÒôÊäÈë·¨ºº×ÖÅÅÁĞ±í
**´´½¨£ºmagicchip
**ÈÕÆÚ£º20080509
*******************************************************************************/
const unsigned char PY_mb_space []={""};
const unsigned char PY_mb_a     []={"°¡°¢ºÇß¹àÄëçï¹"};
const unsigned char PY_mb_ai    []={"°®°«°¤°¥°­°©°¬°¦°§°ª°¯°£°¨´ôàÉæÈè¨êÓŞßíÁàÈïÍö°"};
const unsigned char PY_mb_an    []={"°´°²°µ°¶°³°¸°°°±°·³§¹ãâÖŞîáíï§èñÚÏğÆÛû÷ö"};
const unsigned char PY_mb_ang   []={"°º°¹°»Ñö"};
const unsigned char PY_mb_ao    []={"°À°¼°Á°Â°¾°Ã°½°¿°ÄÏùŞÖæÁâÚæñà»ÛêåÛñúòüéáöË÷¡÷é"};
const unsigned char PY_mb_ba    []={"°Ñ°Ë°É°Ö°Î°Õ°Ï°Í°Å°Ç°Ó°Ô°È°Ğ°Ê°Ì°Ò°ÆôÎÜØá±öÑîÙ÷É"};
const unsigned char PY_mb_bai   []={"°Ù°×°Ú°Ü°Ø°İ°Û²®°ŞŞãßÂêş"};
const unsigned char PY_mb_ban   []={"°ë°ì°à°ã°è°á°æ°ß°å°é°â°ç°ê°ä°íñ­ÛàîÓô²Úæ"};
const unsigned char PY_mb_bang  []={"°ï°ô°ó°õ°÷°î°ñ°ö°ø°ğ°ò°ùäºİò"};
const unsigned char PY_mb_bao   []={"°ü±§±¨±¥±£±©±¡±¦±¬°ş±ªÅÙ±¢°ı±¤°ú°û±«ÅÚÆÙöµæßìÒñÙğ±õÀİá"};
const unsigned char PY_mb_bei   []={"±»±±±¶±­±³±¯±¸±®±°±´±²±µ±º±·±¹±ÛñØã£İíğÇöÍßÂ"};
const unsigned char PY_mb_ben   []={"±¾±¼±½±¿º»ï¼êÚÛÎÛĞ"};
const unsigned char PY_mb_beng  []={"±Ä±Á±Â±À±Å°ö±Ãê´àÔ"};
const unsigned char PY_mb_bi    []={"±È±Ê±Õ±Ç±Ì±Ø±Ü±Æ±Ï±Û±Ë±É±Ú±Í±Ò±×±Ù±Î±Ğ±Ó±Ö±İ±Ñ±ÔÃØÃÚïõŞµİ©ÜÅİÉØ°ñÔî¯ÙÂæÔáùóÙóëó÷ô°ÜêôÅâØîéõÏßÁã¹êÚääå¨èµßÙ÷Âåöåşæ¾"};
const unsigned char PY_mb_bian  []={"±ß±ä±ã±é±à±ç±â±á±Ş±å±æ±èâíí¾ØÒãêíÜòùñÛöıóÖÜĞñ¹ÛÍçÂ"};
const unsigned char PY_mb_biao  []={"±í±ê±ë±ìè¼æ»ì©ì­÷§ñ¦ì®ïğñÑæôïÚ"};
const unsigned char PY_mb_bie   []={"±ğ±ï±î±ñõ¿"};
const unsigned char PY_mb_bin   []={"±ö±ô±÷±ò±ó±õáÙë÷éëçÍ÷ÆÙÏéÄ÷ŞïÙçã"};
const unsigned char PY_mb_bing  []={"²¢²¡±ø±ù±û±ıÆÁ±ü±ú±şŞğéÄÙ÷Úû"};
const unsigned char PY_mb_bo    []={"²¦²¨²¥²´²©²®²µ²£°ş±¡²ª²¤²§²«²±²¯°ã°Ø²°²³²¬²­²²ÆÇ²·íçõËéŞÙñğ¾õÛà£Ş¬ô¤îàâÄë¢"};
const unsigned char PY_mb_bu    []={"²»²½²¹²¼²¿²¶²·²¾²¸±¤²º²ÀÆÒê³åÍêÎîßîĞõ³ß²"};
const unsigned char PY_mb_ca    []={"²Á²ğíåàê"};
const unsigned char PY_mb_cai   []={"²Â²Å²Ä²Æ²Ã²É²Ê²Ç²È²Ë²Ì"};
const unsigned char PY_mb_can   []={"²Ï²Ğ²ô²Î²Ò²Ñ²Í²Óæîè²åî÷õôÓ"};
const unsigned char PY_mb_cang  []={"²Ø²Ö²×²Õ²ÔØ÷"};
const unsigned char PY_mb_cao   []={"²İ²Ù²Ü²Û²ÚàĞô½ó©äî"};
const unsigned char PY_mb_ce    []={"²á²à²ß²â²Şâü"};
const unsigned char PY_mb_cen   []={"²Îá¯ä¹"};
const unsigned char PY_mb_ceng  []={"Ôø²ã²äàá"};
const unsigned char PY_mb_cha   []={"²é²å²æ²è²î²í²ë²ì²ç²êÉ²²ïé«é¶ïïñÃãââÇéßæ±è¾ïÊàê"};
const unsigned char PY_mb_chai  []={"²Ë²ñ²ğ²î²òîÎğûò²Ù­"};
const unsigned char PY_mb_chan  []={"²ú²ø²ô²ó²û²ü²ù²÷²õµ¥²öêèæ¿İÛÚÆÙæâÜåîó¸åñïââãäıìøæöõğå¤"};
const unsigned char PY_mb_chang []={"³¤³ª³£³¡³§³¢³¦³©²ı³¨³«³¥²şÉÑöğë©İÅã®æÏáäÛËãÑâêØöêÆÜÉæ½"};
const unsigned char PY_mb_chao  []={"³¯³­³¬³³³±³²³´³°½Ë´Â³®â÷ìÌñéêË"};
const unsigned char PY_mb_che   []={"³µ³·³¶³¸³¹³ß³ºÛåíº"};
const unsigned char PY_mb_chen  []={"³Ã³Æ³½³¼³¾³¿³Á³Â³Ä³È³À³»é´ŞÓÚÈí×Úßå·ö³àÁØ÷è¡"};
const unsigned char PY_mb_cheng []={"³É³ËÊ¢³Å³Æ³Ç³Ì³Ê³Ï³Í³Ñ³Ò³Î³È³ĞëóèßÛôîñàáîõõ¨êÉñÎèÇòÉØ©îª"};
const unsigned char PY_mb_chi   []={"³Ô³ß³Ù³Ø³á³Õ³à³İ³Ü³Ö³â³Ş³Ú³Û³ã³×õØÛæÜİÜ¯âÁæÊôùñİë·ßêñ¡ò¿à´ğ·í÷ó¤óø÷Îß³áÜó×àÍ"};
const unsigned char PY_mb_chong []={"³åÖØ³æ³ä³è³çÓ¿ÖÖô¾âçô©ï¥ã¿Üû"};
const unsigned char PY_mb_chou  []={"³é³î³ô³ğ³ó³í³ñ³ê³ï³ì³ë³òã°Ù±àüñ¬öÅ"};
const unsigned char PY_mb_chu   []={"³ö´¦³õ³ú³ı´¥³÷³ş´¡´¢Ğó³ü´£´¤³ù³ø³ûèúèÆÛ»âğç©Ø¡ãÀõé÷íòÜéË"};
const unsigned char PY_mb_chuai []={"´§ëúà¨àÜŞõõß"};
const unsigned char PY_mb_chuan []={"´©´¬´«´®´¨´­´ªë°å×îËô­â¶çİ"};
const unsigned char PY_mb_chuang[]={"´°´²´³´´´¯´±âë"};
const unsigned char PY_mb_chui  []={"´µ´¹´¶´¸´·×µé³é¢Úï"};
const unsigned char PY_mb_chun  []={"´º´½´¿´À´¼´¾´»òíİ»ğÈ"};
const unsigned char PY_mb_chuo  []={"´Á´ÂõÖà¨öºê¡"};
const unsigned char PY_mb_ci    []={"´Î´Ë´Ê´É´È´Æ´Å´Ç´Ì´ÄËÅ´Ã´Í²î×ÈßÚğËìôôÙ"};
const unsigned char PY_mb_cong  []={"´Ó´Ô´Ğ´Ò´Ï´ÑçıèÈäÈè®æõÜÊ"};
const unsigned char PY_mb_cou   []={"´Õé¨ê£ëí"};
const unsigned char PY_mb_cu    []={"´Ö´×´Ø´Ù×äáŞâ§İıõ¾õ¡éãõí"};
const unsigned char PY_mb_cuan  []={"´Ü´Ú´ÛÔÜß¥Ùàìàïé"};
const unsigned char PY_mb_cui   []={"´ß´à´İ´ä´Ş´ãË¥´á´âè­ßıã²İÍë¥éÁ"};
const unsigned char PY_mb_cun   []={"´å´ç´æ¶×ââñå"};
const unsigned char PY_mb_cuo   []={"´í´é´ê´ì´ë´èáÏØÈõºëâğîõãğûï±ïó"};
const unsigned char PY_mb_da    []={"´ó´ğ´ï´ò´î´ñËşóÎŞÇßÕñ×ğãâò÷°æ§í³àª÷²"};
const unsigned char PY_mb_dai   []={"´ø´ú´ô´÷´ı´ü´ş´õ´ûµ¡´ö´ó´ùß¾çéåÊá·ß°÷ìææçªÜ¤"};
const unsigned char PY_mb_dan   []={"µ«µ¥µ°µ£µ¯µ§µ¨µ­µ¤µ¢µ©µªµ®µ¦µ¬Ê¯ğãå£ğ÷İÌééíññõóìêæÙÙà¢"};
const unsigned char PY_mb_dang  []={"µ±µ³µ²µµµ´ÚÔîõå´İĞÛÊñÉí¸"};
const unsigned char PY_mb_dao   []={"µ½µÀµ¹µ¶µºµÁµ¾µ·µ¿µ¼µ¸µ»àüôîâáìâë®ß¶"};
const unsigned char PY_mb_de    []={"µÄµØµÃµÂµ×ï½"};
const unsigned char PY_mb_deng  []={"µÈµÆµËµÇ³ÎµÉµÊµÅíãïëàâáØê­ô£"};
const unsigned char PY_mb_di    []={"µØµÚµ×µÍµĞµÖµÎµÛµİµÕµÜµŞµÌµÄµÓÌáµÑµÏµÒµÔµÙêëÛ¡ÚĞÚ®àÖèÜ÷¾ôÆØµé¦íûæ·İ¶íÚïáÛæÙáíÆ"};
const unsigned char PY_mb_dia	[]={"àÇ"};
const unsigned char PY_mb_dian  []={"µãµçµêµîµíµàµßµæµâµëµìµäµèµåµáµéõÚîäÛãÚçñ²ô¡çèáÛñ°"};
const unsigned char PY_mb_diao  []={"µôµöµğµõµñµ÷µóµïµòÄñîöï¢öôõõ"};
const unsigned char PY_mb_die   []={"µùµøµşµúµûµüµıëºÜ¦ğ¬ŞéõŞñóöøÛìà©"};
const unsigned char PY_mb_ding  []={"¶¥¶¨¶¢¶©¶£¶¡¶¤¶¦¶§î®çàîúëëíÖğÛØêñôôúà¤"};
const unsigned char PY_mb_diu   []={"¶ªîû"};
const unsigned char PY_mb_dong  []={"¶¯¶«¶®¶´¶³¶¬¶­¶°¶±¶²á¼ğ´ÛíëËëØíÏë±á´ßË"};
const unsigned char PY_mb_dou   []={"¶¼¶·¶¹¶º¶¸¶¶¶»¶µ¶Áò½ñ¼óûİú"};
const unsigned char PY_mb_du    []={"¶Á¶È¶¾¶É¶Â¶À¶Ç¶Æ¶Ä¶Ã¶Å¶½¶¼¶¿¶Ê¶Ùó¼óÆà½äÂèüë¹÷ò÷ÇÜ¶"};
const unsigned char PY_mb_duan  []={"¶Î¶Ì¶Ï¶Ë¶Í¶Ğé²ìÑóı"};
const unsigned char PY_mb_dui   []={"¶Ô¶Ó¶Ñ¶Ò¶ØïæíÔí¡í­"};
const unsigned char PY_mb_dun   []={"¶Ö¶Ù¶×¶Õ¶Ø¶Û¶Ü¶Ú¶İ²»õ»ãçíïïæíâìÀí»"};
const unsigned char PY_mb_duo   []={"¶à¶ä¶á¶æ¶ç¶â¶å¶è¶é¶Ş¶ßÍÔ¶È¶ãõâãõßÍîìñÖßáç¶"};
const unsigned char PY_mb_e     []={"¶öÅ¶¶î¶ì¶ê¶ó¶í¶ï°¢¶ô¶ë¶ğ¶ñ¶ò¶õï°ÚÌÛÑïÉãÕİàÜÃéîæ¹İ­öùò¦ëñãµßÀØ¬ğÊåí"};
const unsigned char PY_mb_en    []={"¶÷ŞôàÅ"};
const unsigned char PY_mb_er    []={"¶ø¶ş¶ú¶ù¶ü¶û·¡¶ıçíöÜğ¹Ù¦åÇîï"};
const unsigned char PY_mb_fa    []={"·¢·¨·£·¥·¦·¤·§·©ÛÒíÀ"};
const unsigned char PY_mb_fan   []={"·´·¹·­·¬·¸·²·«·µ·º·±·³···¶·®·ª·¯·°ìÜŞÀî²Ş¬õìèóá¦"};
const unsigned char PY_mb_fang  []={"·Å·¿·À·Ä·¼·½·Ã·Â·»·Á·¾îÕáİÚúèÊô³öĞ"};
const unsigned char PY_mb_fei   []={"·Ç·É·Ê·Ñ·Î·Ï·Ë·Í·Ğ·Æ·Ì·Èóõòãëèìéåúì³áôÜÀã­ïĞö­ôäé¼äÇöîç³ğò"};
const unsigned char PY_mb_fen   []={"·Ö·İ·Ò·Û·Ø·Ü·ß·×·Ş·à·Ó·Ù·Ô·Õ·Úèûå¯ö÷çãÙÇ÷÷"};
const unsigned char PY_mb_feng  []={"·ç·â·ê·ì·ä·á·ã·è·ë·î·í·ï·å·æ·éí¿ÙºÛºİ×ããßô"};
const unsigned char PY_mb_fo    []={"·ğ"};
const unsigned char PY_mb_fou   []={"·ñó¾"};
const unsigned char PY_mb_fu    []={"¸±·ù·ö¸¡¸»¸£¸º·ü¸¶¸´·ş¸½¸©¸«¸°¸¿·÷·ò¸¸·û·õ·ó¸³¸¨¸®¸¯¸¹¸¾¸§¸²·ø·ô·ú·ğ·ı¸µ¸¼¸¥¸¢¸¤ÊĞ¸¦¸ª¸¬¸­¸·¸ÀíëíÉÜŞõÃõÆò¶ÜÀöÖá¥ÜòäæòİŞÔİÊòğöûòóç¦ç¨êçî·ïûÙëôïÙìèõİ³æÚğ¥æââöìğß»Û®Ü½åõ"};
const unsigned char PY_mb_ga    []={"¸Á¸ì¼Ğ¸Â¿§ÔşîÅÙ¤ê¸ŞÎæØæÙßÈ"};
const unsigned char PY_mb_gai   []={"¸Ã¸Ä¸Ç¸Å¸Æ½æ¸Èê®ÛòØ¤Úëêà"};
const unsigned char PY_mb_gan   []={"¸Ï¸É¸Ğ¸Ò¸Í¸Ê¸Î¸Ì¸Ë¸Ó¸Ñêºôûí·ğáãïÜÕß¦ç¤éÏä÷äÆŞÏÛá"};
const unsigned char PY_mb_gang  []={"¸Õ¸Ö¸Ù¸Û¸×¸Ú¸Ü¸Ô¸Ø¿¸óàî¸í°"};
const unsigned char PY_mb_gao   []={"¸ß¸ã¸æ¸å¸à¸İ¸á¸â¸ä¸ŞÛ¬Ú¾ê½çÉØºéÀï¯éÂŞ»"};
const unsigned char PY_mb_ge    []={"¸ö¸÷¸è¸î¸ç¸é¸ñ¸ó¸ô¸ï¿©¸ì¸ğ¸ò¸ê¸ë¸í¸ÇÒÙºÏ¸õíÑ÷Àò¢ñËÜªò´ÛÙïÓØîô´ØªàÃëõë¡æüÛÁ"};
const unsigned char PY_mb_gei   []={"¸ø"};
const unsigned char PY_mb_gen   []={"¸ú¸ùßçİ¢Ø¨ôŞ"};
const unsigned char PY_mb_geng  []={"¸ü¸û¾±¹£¹¢¸ı¸ş¹¡âÙöáßìç®"};
const unsigned char PY_mb_gong  []={"¹¤¹«¹¦¹²¹­¹¥¹¬¹©¹§¹°¹±¹ª¹®¹¯¹¨ºìëÅö¡çîò¼"};
const unsigned char PY_mb_gou   []={"¹»¹µ¹·¹³¹´¹º¹¹¹¶¹¸¾äá¸ì°èÛ÷¸êíçÃóÑÚ¸åÜæÅóôØş"};
const unsigned char PY_mb_gu    []={"¹Å¹É¹Ä¹È¹Ê¹Â¹¿¹Ã¹Ë¹Ì¹Í¹À¹¾¹Ç¹¼¹Á¹Æ¼Ö¹½èôğ³ãééïáÄİÔğÀ÷½îÜëûôşßÉöñÚ¬êôî­ì±ïÀêöğóõıòÁî¹ØÅ"};
const unsigned char PY_mb_gua   []={"¹Ò¹Î¹Ï¹Ñ¹Ğ¹ÓØÔßÉëÒğ»èéÚ´"};
const unsigned char PY_mb_guai  []={"¹Ö¹Õ¹ÔŞâ"};
const unsigned char PY_mb_guan  []={"¹Ø¹Ü¹Ù¹Û¹İ¹ß¹Ş¹à¹Ú¹á¹×ÂÚîÂñæİ¸ŞèäÊ÷¤ğÙÙÄ"};
const unsigned char PY_mb_guang []={"¹â¹ã¹äèæáîßÛë×"};
const unsigned char PY_mb_gui   []={"¹é¹ó¹í¹ò¹ì¹æ¹è¹ğ¹ñ¹ê¹î¹ë¹å¹ç¹ô¿ş¹ïÈ²âÑå³èíØÛ÷¬öÙğ§ØĞæ£êĞóşêÁ"};
const unsigned char PY_mb_gun   []={"¹ö¹÷¹õöçÙòíŞçµ"};
const unsigned char PY_mb_guo   []={"¹ı¹ú¹û¹ü¹ø¹ùÎĞÛöé¤ñøÙåâ£áÆŞâàşßÃë½òäòå"};
const unsigned char PY_mb_ha    []={"¹ş¸òÏºîş"};
const unsigned char PY_mb_hai   []={"»¹º£º¦¿Èº¤º¢º§º¡º¥àËõ°ëÜ"};
const unsigned char PY_mb_han   []={"º°º¬º¹º®ºººµº¨º«º¸º­º¯º©º²º±º³º´º¶º·ºªÚõİÕŞşå«ãÛñüòÀìÊò¥êÏ÷ı"};
const unsigned char PY_mb_hang  []={"ĞĞÏïº½º»º¼¿Ôñşãìç¬çñ"};
const unsigned char PY_mb_hao   []={"ºÃºÅºÆº¿º¾ºÂºÁºÀºÄºÑ¸äê»ò«å°àãòºàÆğ©İïå©Ş¶"};
const unsigned char PY_mb_he    []={"ºÍºÈºÏºÓºÌºËºÎºÇºÉºØºÕºÖºĞº×ºÊºÑºÒºÔÏÅàÀÛÀîÁôçãØò¢ÛÖÚ­æüêÂ"};
const unsigned char PY_mb_hei   []={"ºÚºÙ"};
const unsigned char PY_mb_hen   []={"ºÜºİºŞºÛ"};
const unsigned char PY_mb_heng  []={"ºáºãºßºâºàĞĞèìçñŞ¿"};
const unsigned char PY_mb_hong  []={"ºìºäºåºçºéºêºæºèºëÚ§ÙêŞ®ãÈŞ°Ùäİ¦ãü"};
const unsigned char PY_mb_hou   []={"ºóºñºğºíºîºòºïö×óóÜ©ááåËô×÷¿ğú"};
const unsigned char PY_mb_hu    []={"ºş»§ºô»¢ºø»¥ºú»¤ºı»¡ºöºüºûºù»¦ºõÏ·ºËºÍº÷»£ğÉÙüâïğ×óËìæìè÷½ä°ìïõ­çúàñìÃéõğ­ìÎõúğÀâ©ã±á²äïì²ßüéÎ"};
const unsigned char PY_mb_hua   []={"»°»¨»¯»­»ª»®»¬»©»«»íîüèëæèí¹"};
const unsigned char PY_mb_huai  []={"»µ»³»´»±»²»®õ×"};
const unsigned char PY_mb_huan  []={"»»»¹»½»·»¼»º»¶»Ã»Â»Á»À»¿»¸»¾äñâµß§åÕöéÛ¨÷ßå¾Û¼ïÌà÷ä¡İÈçÙä½"};
const unsigned char PY_mb_huang []={"»Æ»Å»Î»Ä»É»Ë»Ê»Ñ»Ì»È»Ç»Ğ»Í»ÏÚòëÁäêóòáåöü"};
const unsigned char PY_mb_hui   []={"»Ø»á»Ò»æ»Ó»ã»Ô»Ù»Ú»İ»Ş»Õ»Ö»à»Û»ß»×»ä»²»Ü»â»ååçä«çõŞ¥à¹í£ßÜêÍãÄ÷âÚ¶ó³Üîä§ßÔò³ÜöçÀ"};
const unsigned char PY_mb_hun   []={"»ì»è»ç»ë»é»êãÔçõâÆäãÚ»"};
const unsigned char PY_mb_huo   []={"»ò»î»ğ»ï»õºÍ»ñ»ö»í»ô»óàëïìñëØåŞ½ß«ïÁó¶îØâ·"};
const unsigned char PY_mb_ji    []={"¼¸¼°¼±¼È¼´»ú¼¦»ı¼Ç¼¶¼«¼Æ¼·¼º¼¾¼Ä¼ÍÏµ»ù¼¤¼ª¼¹¼Ê»÷»ø»û»ş¼¡¼¢¼£¼¥¼§¼¨¼¬¼­¼®¼©¼¯¼²¼³¼µ¼»¼¼¼½¼¿¼À¼Á¼Â¼Ã¼ÅÆÚÆäÆæ¼ÉÆë¼Ë¼Ì¸ø¸ï»üÛÔä©öİåìì´êªöêïúí¶ğ¢ê«ò±ÚµóÅôßóÇØŞß´İğõÒáÕŞáõÕö«ßóçÜÜùñ¤çáî¿Ø¢ÙÊÜ¸Ù¥êåé®÷ÙßÒŞªêé÷ä"};
const unsigned char PY_mb_jia   []={"¼Ò¼Ó¼Ù¼Û¼Ü¼×¼Ñ¼Ğ¼Î¼İ¼Ş¼Ï¼Ô¼Õ¼Ø¼ÚÇÑ¼ÖîòİçåÈê©ä¤ïØğèí¢áµõÊØÅÙ¤ëÎóÕçìğıÛ£ôÂòÌ"};
const unsigned char PY_mb_jian  []={"¼û¼ş¼õ¼â¼ä¼ü¼ú¼ç¼æ½¨¼ì¼ı¼å¼ò¼ô¼ß¼à¼á¼é½¡¼è¼ö½£½¥½¦½§¼øÇ³¼ù¼ñ¼í¼ã¼ó¼î¼ï¼ğ½¢¼÷¼ê¼ë½¤ôå÷µê§ÚÉêğèÅëìõÂçÌŞöê¯ë¦İÑöäóÈÚÙé¥àîå¿ñĞõİíúåÀğÏİóÙÔïµäÕ"};
const unsigned char PY_mb_jiang []={"½«½²½­½±½µ½¬½©½ª½´½¯½®½³Ç¿½°ºçôøíäçÖêññğç­Üüôİä®"};
const unsigned char PY_mb_jiao  []={"½Ğ½Å½»½Ç½Ì½Ï½É¾õ½¹½º½¿½ÊĞ£½Á½¾½Æ½½½Ã½¼½À½¶½Î½Ñ½·½¸½È½Â½Í½Ä½ËáèÜ´ÙÕòÔë¸á½õÓæ¯ğ¨ÜúğÔàİõ´Ù®äĞöŞŞØ"};
const unsigned char PY_mb_jie   []={"½Ó½Ú½Ö½è½Ô½Ø½â½ç½á½ì½ã½Ò½ä½é½×½Ù½æ½ß½à½ê½å¼Û¿¬½Õ½Û½Ü½İ½ë½Ş¼ÒÙÊèîà®Ş×÷ºôÉò»àµò¡öÚæ¼íÙÚ¦æİğÜÚµ"};
const unsigned char PY_mb_jin   []={"½ø½ü½ñ½ö½ô½ğ½ï¾¡¾¢½û½ş½õ½ú½î½ò½÷½í½ó½ı½ùâÛèªâËéÈñÆİÀİ£ñæàäçÆÚáæ¡êáêî"};
const unsigned char PY_mb_jing  []={"¾¹¾²¾®¾ª¾­¾µ¾©¾»¾´¾«¾°¾¯¾º¾³¾¶¾£¾§¾¨¾¬¾±¾¤¾¥¾¦¾¢¾·¾¸ëÂâ°ÚåëæåòØÙã½æºëÖİ¼ÙÓìºåÉö¦ãş"};
const unsigned char PY_mb_jiong []={"¾½¾¼ìçåÄ"};
const unsigned char PY_mb_jiu   []={"¾Í¾Å¾Æ¾É¾Ã¾¾¾È¾À¾Ë¾¿¾Â¾Ç¾Ê¾Á¾Ä¾Ì¾ÎôñğÕõíÙÖèÑèê÷İğ¯ãÎà±"};
const unsigned char PY_mb_ju    []={"¾ä¾Ù¾Ş¾Ö¾ß¾à¾â¾ç¾Ó¾Û¾Ğ¾Õ¾Ø¾Ú¾Ü¾å¾Ï¾Ñ¾ÔÇÒ¾İ¹ñ½Û¾ã³µ¾×¾Ò¾á¾æÙÆõ¶ñÕåğêøÜÚñÀì«ï¸é§ÜÄè¢Şäé°ö´ôòÜìöÂåáéÙõáé·÷¶îÒÚªèÛ"};
const unsigned char PY_mb_juan  []={"¾íÈ¦¾ë¾é¾è¾ê¾ì¾îÛ²ïÃîÃïÔáúèğä¸öÁ"};
const unsigned char PY_mb_jue   []={"¾ö¾ø¾õ½Ç¾ô¾ò¾÷¾ï¾ó¾ñ¾ğ½À½ÅèöàåéÓàµõûØãìßÛÇïãâ±çåáÈŞ§àÙÚÜõêæŞØÊ"};
const unsigned char PY_mb_jun   []={"¾ü¾ı¾ù¾ú¿¡¾ş¹ê¿¢¿¥¾û¿£¿¤óŞ÷åñäŞÜ"};
const unsigned char PY_mb_ka    []={"¿¨¿¦¿©¿§ëÌßÇØû"};
const unsigned char PY_mb_kai   []={"¿ª¿«¿­¿®¿¬ÛîØÜï´îøïÇâéâıİÜ"};
const unsigned char PY_mb_kan   []={"¿´¿³¿°¿¯Ç¶¿²¼÷¿±íèê¬Ù©î«İ¨ãÛ"};
const unsigned char PY_mb_kang  []={"¿¹¿»¿¸¿·¿µ¿¶¿ºîÖãÊØø"};
const unsigned char PY_mb_kao   []={"¿¿¿¼¿¾¿½èàêûåêîí"};
const unsigned char PY_mb_ke    []={"¿È¿É¿Ë¿Ã¿Æ¿Å¿Ì¿Î¿Í¿Ç¿Ê¿Á¿Â¿Ä¿ÀºÇã¡á³òòç¼òÂéğñ½îİë´ò¤î§ï¾ïıçæ÷Áğâà¾äÛæì"};
const unsigned char PY_mb_ken   []={"¿Ï¿Ğ¿Ò¿ÑñÌ"};
const unsigned char PY_mb_keng  []={"¿Ó¿Ôï¬"};
const unsigned char PY_mb_kong  []={"¿Õ¿×¿Ø¿ÖÙÅáÇóí"};
const unsigned char PY_mb_kou   []={"¿Ú¿Û¿Ù¿ÜŞ¢ÜÒíîóØßµ"};
const unsigned char PY_mb_ku    []={"¿Ş¿â¿à¿İ¿ã¿ß¿áØÚ÷¼à·Ü¥ç«"};
const unsigned char PY_mb_kua   []={"¿ç¿å¿æ¿ä¿èÙ¨"};
const unsigned char PY_mb_kuai  []={"¿ì¿é¿ê»á¿ëßàØáä«Û¦áöëÚ"};
const unsigned char PY_mb_kuan  []={"¿í¿î÷Å"};
const unsigned char PY_mb_kuang []={"¿ó¿ğ¿ñ¿ò¿ö¿õ¿ï¿ôÚ¿Ú÷æşŞÅÚ²ÛÛêÜßÑ"};
const unsigned char PY_mb_kui   []={"¿÷À¢¿ü¿úÀ£¿û¿ıÀ¡¿ø¿ş¿ùØÑã´Şñî¥õÍñùóñà­åÓêÒİŞã¦à°Ø¸òñÚóÙç"};
const unsigned char PY_mb_kun   []={"À¦À§À¥À¤öïï¿÷Õçûõ«ãÍã§"};
const unsigned char PY_mb_kuo   []={"À«À©À¨ÀªÊÊòÒèé"};
const unsigned char PY_mb_la    []={"À­À²À±À¯À°À®À¬À¶ÂäğøååíÇØİê¹"};
const unsigned char PY_mb_lai   []={"À´ÀµÀ³áÁáâäµäşêãíùïªñ®ô¥"};
const unsigned char PY_mb_lan   []={"À¶À¼ÀÃÀ¹ÀºÀÁÀ¸À¿ÀÂÀÄÀ»À¾À·À½ÀÀé­á°ñÜïçìµî½äí"};
const unsigned char PY_mb_lang  []={"ÀËÀÇÀÈÀÉÀÊÀÆÀÅïüòëİ¹à¥ï¶ãÏİõ"};
const unsigned char PY_mb_lao   []={"ÀÏÀÌÀÎÀÍÀÓÀÔÂäÀÑÀÒÂçÀĞÁÊñìï©õ²îîßëèááÀğì"};
const unsigned char PY_mb_le    []={"ÁËÀÖÀÕÀßØìß·ãî÷¦"};
const unsigned char PY_mb_lei   []={"ÀàÀÛÀáÀ×ÀİÀÕÀŞÀÙÀßÀØÀÜÀÚçĞÚ³ñçõªÙúæĞéÛàÏ"};
const unsigned char PY_mb_leng  []={"ÀäÀâÀãÜ¨ã¶"};
const unsigned char PY_mb_li    []={"ÀïÀëÁ¦Á¢ÀîÀıÁ¨ÀíÀûÀæÀåÀñÀúÀöÀôÀçÀèÀéÀêÀìÀğÀòÀóÀõÀ÷ÀøÀùÀüÀşÁ¡Á£Á¤Á¥Á§Ù³ÙµÛªÛŞÜÂİ°İñğ¿óÒ÷¯çÊõÈòÛï®ã¦å¢ôÏèÀó»Øªß¿íÂæËóöğİğßáûŞ¼äàöâìåèİà¦õ·éöîºæêî¾åÎà¬ö¨÷óòÃæ²"};
const unsigned char PY_mb_lia	[]={"Á©"};
const unsigned char PY_mb_lian  []={"Á¬ÁªÁ·Á«ÁµÁ³Á¶Á´Á²Á¯Á®Á±Á­Á°ó¹çöéçİüöãŞÆäòì¡ñÍå¥ñÏé¬"};
const unsigned char PY_mb_liang []={"Á½ÁÁÁ¾Á¹Á¸ÁºÁ¿Á¼ÁÀÁÂÁ©Á»Ü®ö¦õÔé£÷Ëİ¹"};
const unsigned char PY_mb_liao  []={"ÁËÁÏÁÃÁÄÁÌÁÆÁÎÁÇÁÉÁÅÁÈÁÍÁÊîÉŞ¤ŞÍå¼çÔâ²ğÓàÚ"};
const unsigned char PY_mb_lie   []={"ÁĞÁÑÁÔÁÓÁÒßÖÛøŞæ÷àôóõñÙıä£"};
const unsigned char PY_mb_lin   []={"ÁÖÁÙÁÜÁÚÁ×ÁÛÁŞÁßÁàÁÕÁØÁİåàá×İşôÔ÷ëõïê¥âŞãÁî¬éİì¢ßø"};
const unsigned char PY_mb_ling  []={"ÁíÁîÁìÁãÁåÁáÁéÁëÁäÁèÁêÁâÁæÁçÀâôáòÈÜßç±ê²Û¹ßÊãöèùèÚöìñöàò"};
const unsigned char PY_mb_liu   []={"ÁùÁ÷ÁôÁõÁøÁïÁòÁöÁñÁğÁóÂµÂ½ç¸ï³öÌïÖä¯æòì¼ğÒìÖåŞ"};
const unsigned char PY_mb_long  []={"ÁúÂ£ÁıÁûÂ¡Â¢ÅªÁüÁşÂ¤ÛâëÊççÜ×ãñèĞñªíÃ"};
const unsigned char PY_mb_lou   []={"Â¥Â§Â©ÂªÂ¶Â¦Â¨ÙÍò÷ïÎİäñï÷Ãà¶ğüáĞ"};
const unsigned char PY_mb_lu    []={"Â·Â¶Â¼Â¹Â½Â¯Â¬Â³Â±Â«Â­Â®ÂµÂ°ÂÌÂ²Â¸Â¾ÂºÂ»Â´ÁùöÔèÓäËŞ¤åÖãòéñëªóüéÖéûÛäëÍàà"};
const unsigned char PY_mb_luan  []={"ÂÒÂÑÂĞÂÍÂÏÂÎèïöÇÙõæ®ğ½"};
const unsigned char PY_mb_lue   []={"ÂÔÂÓï²"};
const unsigned char PY_mb_lun   []={"ÂÛÂÖÂÕÂ×ÂÙÂØÂÚàğ"};
const unsigned char PY_mb_luo   []={"ÂäÂŞÂàÂãÂâÀÓÂáÂİÂÜÂåÂæÂßÂç¿©ÜıäğÙùöÃÙÀíÑé¡ŞÛëáñ§Şûãøçóïİâ¤"};
const unsigned char PY_mb_lv    []={"ÂÌÂÊÂÁÂ¿ÂÃÂÅÂËÂÀÂÉÂÈÂÆÂÂÂÇÂÄÙÍëöéµãÌŞÛñÚïù"};
const unsigned char PY_mb_ma    []={"ÂğÂèÂíÂïÂéÂîÄ¨ÂëÂêÂìÄ¦ßéó¡áïæÖè¿"};
const unsigned char PY_mb_mai   []={"ÂòÂôÂõÂñÂóÂöÛ½ö²İ¤"};
const unsigned char PY_mb_man   []={"ÂúÂıÂ÷ÂşÂùÂûÂüÂøÂñÃ¡á£÷©Ü¬òıïÜò©÷´çÏì×"};
const unsigned char PY_mb_mang  []={"Ã¦Ã¢Ã¤Ã§Ã£Ã¥íËÚøòşäİ"};
const unsigned char PY_mb_mao   []={"Ã«Ã°Ã±Ã¨Ã¬Ã®Ã²Ã¯Ã³Ã­ÃªÃ©ë£Üâè£òú÷Öí®êÄêóî¦á¹Ùóó±ì¸ã÷"};
const unsigned char PY_mb_me    []={"Ã´÷á"};
const unsigned char PY_mb_mei   []={"Ã»Ã¿ÃºÃ¾ÃÀÃ¸ÃÃÃ¶Ã¹ÃµÃ¼Ã·ÃÂÃÁÃ½ÃÓÃÄÃÕÄ­áÒâ­ñÇäØä¼ğÌİ®÷ÈïÑé¹"};
const unsigned char PY_mb_men   []={"ÃÅÃÇÃÆŞÑìËí¯îÍ"};
const unsigned char PY_mb_meng  []={"ÃÍÃÎÃÉÃÌÃÏÃËÃÊÃÈÃ¥íæòìÛÂãÂİùó·òµëüô»ô¿Ş«"};
const unsigned char PY_mb_mi    []={"Ã×ÃÜÃÔÃĞÃÛÃÕÃÙÃØÃÖÃİÃÒÃÓÃÚÃÑŞÂ÷ãßäãè÷çìòâ¨åôÚ×ØÂëßåµôÍà×ôé"};
const unsigned char PY_mb_mian  []={"ÃæÃŞÃâÃàÃßÃåÃãÃáÃäëïäÏííãæö¼äÅ"};
const unsigned char PY_mb_miao  []={"ÃëÃçÃíÃîÃèÃéÃêÃìíğçÑç¿åãíµß÷èÂğÅ"};
const unsigned char PY_mb_mie   []={"ÃğÃïßãóúóºØ¿"};
const unsigned char PY_mb_min   []={"ÃñÃòÃôÃöÃóÃõçëíªçÅãÉçäÜåãıö¼÷ªáº"};
const unsigned char PY_mb_ming  []={"ÃûÃ÷ÃüÃùÃúÃøÃËÚ¤î¨êÔÜøäéõ¤"};
const unsigned char PY_mb_miu   []={"ÃıçÑ"};
const unsigned char PY_mb_mo    []={"ÃşÄ¥Ä¨Ä©Ä¤Ä«Ã»ÄªÄ¬Ä§Ä£Ä¦Ä¡Ä®Ä°ÂöÄ­ÍòÎŞÃ°Ä¯ï÷İë÷áÜÔºÙæÖÄ¢ñ¢éâïÒæÆÚÓõöõøâÉñò"};
const unsigned char PY_mb_mou   []={"Ä³Ä±Ä²íøòÖöÊÙ°çÑßè"};
const unsigned char PY_mb_mu    []={"Ä¾Ä¸Ä¶Ä»Ä¿Ä¹ÄÁÄ²Ä£ÄÂÄºÄµÄ´Ä¼Ä½ÄÀÄ·ÀÑîâë¤ÛéãåØïÜÙ"};
const unsigned char PY_mb_na    []={"ÄÇÄÃÄÄÄÉÄÆÄÈÄÅÄÏñÄŞàïÕëÇ"};
const unsigned char PY_mb_nai   []={"ÄËÄÍÄÌÄÎÄÊÄÄİÁÜµèÍØ¾Ù¦"};
const unsigned char PY_mb_nan   []={"ÄÑÄÏÄĞôöàïòïéªà«ëî"};
const unsigned char PY_mb_nang  []={"ÄÒâÎêÙàìß­"};
const unsigned char PY_mb_nao   []={"ÄÖÄÔÄÕÄÓÄ×Ø«îóè§ÛñßÎòÍâ®íĞ"};
const unsigned char PY_mb_ne    []={"ÄØÄÄÄÇÄÅÚ«"};
const unsigned char PY_mb_nei   []={"ÄÚÄÄÄÙÄÇ"};
const unsigned char PY_mb_nen   []={"ÄÛí¥"};
const unsigned char PY_mb_neng  []={"ÄÜ"};
const unsigned char PY_mb_ni    []={"ÄãÄàÄâÄåÄæÄØÄçÄßÄáÄäÄİÄŞîêêÇÛèìòâ¥Ù£âõöòíşì»"};
const unsigned char PY_mb_nian  []={"ÄêÄîÄíÄìÄéÄëÄèÕ³Ø¥ğ¤éıöÓöóÛş"};
const unsigned char PY_mb_niang []={"ÄïÄğ"};
const unsigned char PY_mb_niao  []={"ÄñÄòôÁÜàëåæÕ"};
const unsigned char PY_mb_nie   []={"ÄóÄøÄôÄõÄùÄ÷ÄöÚíŞÁà¿ô«õæò¨Ø¿"};
const unsigned char PY_mb_nin   []={"Äúí¥"};
const unsigned char PY_mb_ning  []={"Å¡ÄıÄşÄûÄüÅ¢Øúå¸ßÌñ÷"};
const unsigned char PY_mb_niu   []={"Å£Å¤Å¦Å¥áğâîæ¤ŞÖ"};
const unsigned char PY_mb_nong  []={"ÅªÅ¨Å©Å§ßæÙ¯"};
const unsigned char PY_mb_nu    []={"Å­Å¬Å«æÛæÀæååó"};
const unsigned char PY_mb_nuan  []={"Å¯"};
const unsigned char PY_mb_nue   []={"Å°Å±ÚÊ"};
const unsigned char PY_mb_nuo   []={"Å²ÅµÅ³Å´ÄÈßöÙĞï»Şù"};
const unsigned char PY_mb_nv    []={"Å®îÏí¤ô¬"};
const unsigned char PY_mb_o     []={"Å¶à¸àŞ"};
const unsigned char PY_mb_ou    []={"Å¼Å»Å·ÅºÅ¸ÇøÅ½Å¹âæê±Ú©ñî"};
const unsigned char PY_mb_pa    []={"ÅÂÅÀÅ¿Å¾°Ò°ÇÅÁÅÃÅÉóáèËİâ"};
const unsigned char PY_mb_pai   []={"ÅÉÅÅÅÄÅÆÆÈÅÇÅÈßßÙ½İå"};
const unsigned char PY_mb_pan   []={"ÅÌÅÎÅĞÅÊÅÏÅËÅÑÅÍ·¬°ãÅÖñáó´ñÈãúŞÕãİõç"};
const unsigned char PY_mb_pang  []={"ÅÔÅÖÅÕÅÓÅÒ°ò°õäèáİåÌó¦"};
const unsigned char PY_mb_pao   []={"ÅÜÅ×ÅÚÅİÅÙÅÛÅØáóŞËâÒğåëã"};
const unsigned char PY_mb_pei   []={"ÅãÅäÅâÅŞÅßÅåÅàÅæÅáì·ïÂàúõ¬ö¬àÎ"};
const unsigned char PY_mb_pen   []={"ÅçÅèäÔ"};
const unsigned char PY_mb_peng  []={"ÅöÅõÅïÅéÅîÅóÅíÅôÅëÅğÅòÅêÅìÅñâñÜ¡ó²àØ"};
const unsigned char PY_mb_pi    []={"ÅúÆ¤ÅûÆ¥Åü±ÙÅ÷Æ¨Æ¢Æ§Æ£Æ¦ÅùÅıÅşÆ¡Æ©Åø·ñõùØ§ÛÜæÇñ±Øòß¨Û¯ê¶èÁî¢òçÜ±ÚüßÁÚéîëâÏî¼Ûıç¢ÚğäÄàèò·ñÔ"};
const unsigned char PY_mb_pian  []={"Æ¬ÆªÆ­Æ«±ã±âôæçÂêúæéëİõäÚÒ"};
const unsigned char PY_mb_piao  []={"Æ±Æ®Æ¯Æ°ÆÓóªİ³æÎî©éèçÎàÑæôØâ"};
const unsigned char PY_mb_pie   []={"Æ³Æ²ÜÖë­"};
const unsigned char PY_mb_pin   []={"Æ·Æ¶Æ¸Æ´ÆµæÉé¯æ°êòò­"};
const unsigned char PY_mb_ping  []={"Æ½Æ¾Æ¿ÆÀÆÁÆ¹Æ¼Æ»Æº·ëæ³öÒèÒÙ·"};
const unsigned char PY_mb_po    []={"ÆÆÆÂÆÄÆÅÆÃÆÈ²´ÆÇÆÓ·±ÆÉóÍğ«îÇÚéÛ¶ê·ØÏçêîŞ"};
const unsigned char PY_mb_pou   []={"ÆÊŞåÙö"};
const unsigned char PY_mb_pu    []={"ÆËÆÌÆ×¸¬ÆÍÆÑÆÏÆÓÆĞÆØÆÎÆÙÆÒÆÔÆÖ±¤ÆÕ±©ïèàÛÙéäßå§ë«õëè±ïäƒW"};
const unsigned char PY_mb_qi    []={"ÆğÆäÆßÆøÆÚÆëÆ÷ÆŞÆïÆûÆåÆæÆÛÆáÆôÆİÆâÆñÆöÆúÆüÆîÆàÆóÆòÆõÆçÆíÆÜÆèÆêÆé»üÆù¼©ÆãÆıÆìì÷ñıæëá¨áªõèİ½Ş­èçí¬ÜÎÜùİÂÜ»ãàØ½÷¢Ù¹éÊàÒòÓôëØÁì¥ç÷÷èçùòàÛßè½İİíÓä¿ìóêÈç²"};
const unsigned char PY_mb_qia   []={"Ç¡¿¨ÆşÇ¢ñÊİÖ÷Ä"};
const unsigned char PY_mb_qian  []={"Ç°Ç®Ç§Ç£Ç³Ç©Ç·Ç¦Ç¶Ç¥Ç¨Ç¯Ç¬Ç´Ç«Ç±Ç¸ÏËÇ¤Ç²Ç­ÇµÇªá©îÔå½óéŞçåºÙ»ã»ã¥í©ò¯ÜÍİ¡ç×ÙİÜ·ÚäëÉÜçèıêùå¹"};
const unsigned char PY_mb_qiang []={"Ç¿Ç¹Ç½ÇÀÇ»ÇºÇ¼Ç¾½«òŞõÄê¨ñßãŞìÁïêïºïÏôÇéÉæÍ"};
const unsigned char PY_mb_qiao  []={"ÇÅÇÆÇÃÇÉÇÌÇÂ¿ÇÇÊÇËÇÄÇÎÇÏÈ¸ÇÇÇÈÇÍÇÁéÔÜñõÎíÍã¾ÚÛ÷³ã¸çØÚ½Øä"};
const unsigned char PY_mb_qie   []={"ÇĞÇÒÇÓÇÔÇÑÆöÛ§ôòã«ïÆæªóæã»Ù¤êü"};
const unsigned char PY_mb_qin   []={"Ç×ÇÙÇÖÇÚÇÜÇŞÇØÇÛÇßÇİÇÕßÄñûñæôÀÜËäÚâÛàºòûàßŞìéÕï·"};
const unsigned char PY_mb_qing  []={"ÇëÇáÇåÇàÇéÇçÇâÇãÇìÇæÇêÇ×ÇäÇèàõö¥éÑóäÜÜòß÷ôóÀöëíàôì"};
const unsigned char PY_mb_qiong []={"ÇîÇíõ¼ñ·ÚöòËÜäöÆóÌ"};
const unsigned char PY_mb_qiu   []={"ÇóÇòÇïÇğÇö³ğÇñÇôÇõ¹êé±òÇôÃôÜòøÛÏåÏÙ´ò°êäöúáìäĞ÷üåÙ"};
const unsigned char PY_mb_qu    []={"È¥È¡ÇøÈ¢ÇşÇúÇ÷È¤ÇüÇıÇùÇûÈ£Ğçó½Ş¾ìîŞ¡íáÛ¾Ú°ğ¶ãÖôğñ³áé÷ñè³ë¬êïòĞëÔöÄá«ÜÄ"};
const unsigned char PY_mb_quan  []={"È«È¨È°È¦È­È®ÈªÈ¯È§È¬È©îıóÜç¹Ú¹éúî°÷ÜãªòéÜõ"};
const unsigned char PY_mb_que   []={"È´È±È·È¸È³ÈµÈ²È¶ãÚã×í¨"};
const unsigned char PY_mb_qun   []={"ÈºÈ¹åÒ÷å"};
const unsigned char PY_mb_ran   []={"È¾È¼È»È½÷×ÜÛòÅ"};
const unsigned char PY_mb_rang  []={"ÈÃÈÂÈ¿ÈÁÈÀğ¦ìü"};
const unsigned char PY_mb_rao   []={"ÈÄÈÆÈÅÜéèãæ¬"};
const unsigned char PY_mb_re    []={"ÈÈÈôÈÇßö"};
const unsigned char PY_mb_ren   []={"ÈËÈÎÈÌÈÏÈĞÈÊÈÍÈÑÈÒÈÉâ¿éíØğÜóİØñÅïş"};
const unsigned char PY_mb_reng  []={"ÈÓÈÔ"};
const unsigned char PY_mb_ri    []={"ÈÕ"};
const unsigned char PY_mb_rong  []={"ÈİÈŞÈÚÈÜÈÛÈÙÈÖÈØÈßÈ×éÅáõáÉëÀòî"};
const unsigned char PY_mb_rou   []={"ÈâÈàÈáôÛõå÷·"};
const unsigned char PY_mb_ru    []={"ÈçÈëÈêÈåÈãÈéÈìÈèÈäÈæİêñàï¨àéçÈå¦Ş¸ò¬äáä²"};
const unsigned char PY_mb_ruan  []={"ÈíÈîëÃ"};
const unsigned char PY_mb_rui   []={"ÈğÈïÈñî£ÜÇò¸èÄŞ¨"};
const unsigned char PY_mb_run   []={"ÈòÈó"};
const unsigned char PY_mb_ruo   []={"ÈôÈõÙ¼óè"};
const unsigned char PY_mb_sa    []={"ÈöÈ÷ÈøêıØíØ¦ìªëÛ"};
const unsigned char PY_mb_sai   []={"ÈûÈùÈúË¼Èüàç"};
const unsigned char PY_mb_san   []={"ÈıÉ¢É¡ÈşâÌôÖë§ö±"};
const unsigned char PY_mb_sang  []={"É£É¥É¤òªíßŞú"};
const unsigned char PY_mb_sao   []={"É¨É©É¦É§ÉÒÜ£öşëıçÒğş"};
const unsigned char PY_mb_se    []={"É«É¬ÉªÈûØÄï¤ğ£"};
const unsigned char PY_mb_sen   []={"É­"};
const unsigned char PY_mb_seng  []={"É®"};
const unsigned char PY_mb_sha   []={"É±É³É¶É´ÉµÉ°É²É¯ÏÃÉ·É¼àÄßşöèö®ï¡ğğôÄêıì¦"};
const unsigned char PY_mb_shai  []={"É¹É¸É«õ§"};
const unsigned char PY_mb_shan  []={"É½ÉÁÉÀÉÆÉÈÉ¼É¾É¿µ¥Éº²ôÉÄÕ¤É»µ§ÉÅÉÂÉÇÉÃÉÉæÓóµÜÏìøõÇÛ·äú÷­æ©ØßæóğŞëşÚ¨îÌô®Ûï"};
const unsigned char PY_mb_shang []={"ÉÏÉËÉĞÉÌÉÍÉÎÉÊÌÀÉÑìØõüç´éäÛğ"};
const unsigned char PY_mb_shao  []={"ÉÙÉÕÉÓÉÚÉ×ÉÒÉÔÉÛÉØÉÜÉÖÕÙÇÊÜæÛ¿äûô¹òÙóâ"};
const unsigned char PY_mb_she   []={"ÉçÉäÉßÉèÉàÉãÉáÕÛÉæÉŞÉâÉåÉİì¨ØÇî´â¦÷êäÜÙÜ"};
const unsigned char PY_mb_shen  []={"ÉíÉìÉîÉôÉñÉõÉøÉöÉóÉêÉòÉğÉë²ÎÉéÊ²ÉïÉ÷İØôÖİ·Ú·ÚÅïòé©äÉò×ßÓëÏ"};
const unsigned char PY_mb_sheng []={"ÉùÊ¡Ê£ÉúÉıÉşÊ¤Ê¢Ê¥ÉûÉü³ËêÉäÅíòóÏáÓ"};
const unsigned char PY_mb_shi   []={"ÊÇÊ¹Ê®Ê±ÊÂÊÒÊĞÊ¯Ê¦ÊÔÊ·Ê½Ê¶Ê­Ê¸Ê°ÊºÊ»Ê¼ËÆĞêÊ¾Ê¿ÊÀÊÁ³×ÊÃÊÄÊÅÊÆÊ²Ö³ÖÅÊÈÊÉÊ§ÊÊÊËÊÌÊÍÊÎÊÏÊ¨Ê³ÊÑÊ´ÊÓÊµÊ©ÊªÊ«Ê¬õ¹İªÛõîæóÂöåöõêÛéøİéóßìÂÚÖß±õ§ó§"};
const unsigned char PY_mb_shou  []={"ÊÖÊÜÊÕÊ×ÊØÊİÊÚÊŞÊÛÊìÊÙô¼á÷ç·"};
const unsigned char PY_mb_shu   []={"ÊéÊ÷ÊıÊìÊäÊáÊåÊôÊøÊõÊöÊñÊòÊóÊçÊêÊëÊßÊèÊùÊúÊûÊüÊíÊşË¡ÊàÊîÊâÊãÊïÊğÊææ­Şóïø"};
const unsigned char PY_mb_shua  []={"Ë¢Ë£à§"};
const unsigned char PY_mb_shuai []={"Ë¤Ë¦ÂÊË§Ë¥ó°"};
const unsigned char PY_mb_shuan []={"Ë¨Ë©ãÅäÌ"};
const unsigned char PY_mb_shuang[]={"Ë«ËªË¬ãñæ×"};
const unsigned char PY_mb_shui  []={"Ë®Ë­Ë¯Ë°Ëµ"};
const unsigned char PY_mb_shun  []={"Ë³Ë±Ë²Ë´"};
const unsigned char PY_mb_shuo  []={"ËµÊıË¶Ë¸Ë·Ş÷åùéÃİôîå"};
const unsigned char PY_mb_si    []={"ËÄËÀË¿ËºËÆË½Ë»Ë¼ËÂË¾Ë¹Ê³ËÅ²ŞËÁËÇËÃËÈñêæáÙîòÏØËãáïÈãôóÓßĞğ¸æ¦ÛÌçÁìëäùÙ¹"};
const unsigned char PY_mb_song  []={"ËÍËÉËÊËÎËÌËĞËËËÏñµİ¿äÁã¤áÔÚ¡áÂâì"};
const unsigned char PY_mb_sou   []={"ËÒËÑËÓËÔàÕà²ì¬ÛÅŞ´ïËâÈî¤äÑòôËÓ"};
const unsigned char PY_mb_su    []={"ËØËÙËßËÜËŞË×ËÕËàËÚËÖËõËİËÛãºóùö¢öÕÙíà¼ÚÕİøä³"};
const unsigned char PY_mb_suan  []={"ËáËãËââ¡"};
const unsigned char PY_mb_sui   []={"ËêËæËéËäËëËìÄòËåËèËçËíËîíõÚÇå¡åäìİİ´î¡"};
const unsigned char PY_mb_sun   []={"ËïËğËñé¾İ¥â¸áøöÀ"};
const unsigned char PY_mb_suo   []={"ËùËõËøËöË÷ËóËòÉ¯ËôêıíüàÊßïèøàÂæ¶ôÈ"};
const unsigned char PY_mb_ta    []={"ËûËıËüÌ¤ËşËúÍØÌ¡Ì¢Ì£äâõÁ÷£í³é½äğåİîèãËàª"};
const unsigned char PY_mb_tai   []={"Ì«Ì§Ì¨Ì¬Ì¥Ì¦Ì©ÌªÌ­ìÆëÄõÌß¾öØîÑŞ·Û¢ææ"};
const unsigned char PY_mb_tan   []={"Ì¸Ì¾Ì½Ì²µ¯Ì¼Ì¯Ì¶Ì°Ì³ÌµÌºÌ¹Ì¿Ì±Ì·Ì®Ì´Ì»Û°ê¼ìşîãïÄå£ïâñû"};
const unsigned char PY_mb_tang  []={"ÌÉÌËÌÃÌÇÌÀÌÁÌÌÌÈÌÊÌÆÌÂÌÄÌÅó«éÌôÊõ±è©ïÛÙÎâ¼äçñíàûï¦ó¥"};
const unsigned char PY_mb_tao   []={"Ì×ÌÍÌÓÌÒÌÖÌÔÌÎÌÏÌÕÌĞÌÑØ»ßûä¬èº÷Òß¶ìâ"};
const unsigned char PY_mb_te    []={"ÌØìıí«ï«ß¯"};
const unsigned char PY_mb_teng  []={"ÌÛÌÚÌÙÌÜëø"};
const unsigned char PY_mb_ti    []={"ÌáÌæÌåÌâÌßÌãÌêÌŞÌİÌàÌäÌéÌçÌèÌëõ®ğÃç°ç¾ÙÃñÓåÑÜèã©"};
const unsigned char PY_mb_tian  []={"ÌìÌïÌíÌîÌğÌòÌñÌóµèŞİîäãÙãÃéåî±"};
const unsigned char PY_mb_tiao  []={"ÌõÌøÌôµ÷ÌöÌ÷ö¶óÔìöòè÷ØÙ¬ñ»öæÜæôĞ"};
const unsigned char PY_mb_tie   []={"ÌúÌùÌûİÆ÷Ñ"};
const unsigned char PY_mb_ting  []={"ÌıÍ£Í¦ÌüÍ¤Í§Í¥Í¢ÌşÍ¡ÜğİãæÃèèòÑöªî®îú"};
const unsigned char PY_mb_tong  []={"Í¬Í¨Í´Í­Í°Í²Í±Í³Í¯Í®Í©Í«¶²¶±ÍªäüÜíÙÚíÅá¼âúÙ¡àÌÛí"};
const unsigned char PY_mb_tou   []={"Í·ÍµÍ¸Í¶î×÷»"};
const unsigned char PY_mb_tu    []={"ÍÁÍ¼ÍÃÍ¿ÍÂÍºÍ»Í½Í¹Í¾ÍÀÜ¢İ±İËîÊõ©"};
const unsigned char PY_mb_tuan  []={"ÍÅÍÄî¶ŞÒåè"};
const unsigned char PY_mb_tui   []={"ÍÈÍÆÍËÍÊÍÇÍÉìÕß¯"};
const unsigned char PY_mb_tun   []={"ÍÌÍÍÍÊÍÎ¶ÚÙÛâ½êÕëà"};
const unsigned char PY_mb_tuo   []={"ÍÏÍÑÍĞÍ×ÍÔÍØÍÕÍÖÍÙÍÒÍÓÆÇØ±Ù¢ÛçâÕãûèØèŞéÒõÉóêõ¢íÈö¾"};
const unsigned char PY_mb_wa    []={"ÍÚÍßÍÜÍÛÍŞÍİ°¼ÍàØôæ´ëğ"};
const unsigned char PY_mb_wai   []={"ÍâÍááË"};
const unsigned char PY_mb_wan   []={"ÍêÍòÍíÍëÍæÍäÍìÍåÍèÍóÍğÍñÍéÍçÍãÍïÃäÍîÂûİ¸ëäòêçºÜ¹çşæıØàîµİÒ"};
const unsigned char PY_mb_wang  []={"ÍûÍüÍõÍùÍøÍöÍ÷ÍúÍôÍıÃ¢Øèã¯éş÷Í"};
const unsigned char PY_mb_wei   []={"ÎªÎ»Î´Î§Î¹Î¸Î¢Î¶Î²Î±ÍşÎ°ÎÀÎ£Î¥Î¯ÎºÎ¨Î¬Î·Î©Î¤Î¡ÎµÎ½Î¾Î«Î³Î¿Î¦Î®Î­Î¼ÒÅİÚàøôºöÛæ¸åÔãÇÚñãíçâä¶á¡áËÚóÚÃä¢ÙËâ«â¬áÍê¦è¸ì¿ìĞÛ×Ş±ğô"};
const unsigned char PY_mb_wen   []={"ÎÊÎÄÎÅÎÈÎÂÎÇÎÃÎÆÎÁÎÉãëãÓØØö©è·"};
const unsigned char PY_mb_weng  []={"ÎÌÎËÎÍİîŞ³"};
const unsigned char PY_mb_wo    []={"ÎÒÎÕÎÑÎÔÎÎÎÖÎÏÎĞÎÓÙÁá¢ö»ë¿İ«à¸ä×íÒ"};
const unsigned char PY_mb_wu    []={"ÎŞÎåÎİÎïÎèÎíÎóÎæÎÛÎòÎğÎÙÎäÎìÎñÎØÎéÎâÎçÎáÎêÎÚÎã¶ñÎÜÎßÎ×ÎîÎàÎëåüòÚêõå»Ø£âäÚãÚùâèæğì¶öÈØõè»ğÍæÄåÃğíÜÌìÉßíâĞğÄ÷ùä´ÛØ"};
const unsigned char PY_mb_xi    []={"Î÷Ï´Ï¸ÎüÏ·ÏµÏ²Ï¯Ï¡ÏªÏ¨ÎıÏ¥Ï¢Ï®Ï§Ï°ÎûÏ¦Ï¤ÎùÎõÏ£Ï­ÎşÎúÎôÏ±ÎøÏ³Ï©À°ÎöÏ¶ÆÜÏ«Ï¬òáŞÉä»İßâ¾åïçôæÒìùÙâôâñ¶ìûÙÒäÀİûô¸õèõµì¤ğªó¬ôËÜçáãÚôÛ­ßñêØó£ì¨éØãÒôÑìäêêİ¾÷ûñÓôª"};
const unsigned char PY_mb_xia   []={"ÏÂÏÅÏÄÏ¿ÏºÏ¹Ï¼ÏÁÏ»ÏÀÏ½ÏÃÏ¾»£áòåÚè¦èÔíÌóÁ÷ïßÈ"};
const unsigned char PY_mb_xian  []={"ÏÈÏßÏØÏÖÏÔÏÆÏĞÏ×ÏÓÏİÏÕÏÊÏÒÏÎÏÚÏŞÏÌÏÇÏÉÏÙÏÍÏËÏÜÏÏÏÑÏÛÏ³¼ûÜÈŞºá­ğïİ²ôÌæµò¹áıììÙşìŞõĞõÑõ£åßë¯ğÂóÚö±"};
const unsigned char PY_mb_xiang []={"ÏëÏòÏóÏîÏìÏãÏçÏàÏñÏäÏïÏíÏâÏá½µÏèÏéÏğÏêÏæÏåÜ¼İÙâÃâÔæøç½ó­öß÷Ï"};
const unsigned char PY_mb_xiao  []={"Ğ¡Ğ¦ÏûÏ÷ÏúÏôĞ§ÏüÏşĞ¤Ğ¢ÏõĞ¥ÏöÏøÏùĞ£æçßØäìåĞèÉç¯ÏıáÅóïèÕóã÷ÌòÙ"};
const unsigned char PY_mb_xie   []={"Ğ´Ğ©Ğ¬ĞªĞ±ÑªĞ»Ğ¶Ğ®Ğ¼Ğ·ĞºĞ¸Ğ¹Ğ¨Ğ°Ğ­ĞµĞ³Ğ«Ğ¯Ğ²½âÆõÒ¶ç¥ò¡çÓâ³é¿âİß¢ÙÉå¬äÍÙôéÇåâŞ¯õóÛÆÛÄ"};
const unsigned char PY_mb_xin   []={"ĞÂĞÄĞÀĞÅĞ¾Ğ½Ğ¿ĞÁÑ°ĞÆĞÃì§Ø¶İ·Ü°öÎê¿ïâ"};
const unsigned char PY_mb_xing  []={"ĞÔĞĞĞÍĞÎĞÇĞÑĞÕĞÈĞÌĞÓĞËĞÒĞÏĞÉĞÊÊ¡íÊã¬ÜşÚêß©Üô"};
const unsigned char PY_mb_xiong []={"ĞØĞÛĞ×ĞÖĞÜĞÚĞÙÜº"};
const unsigned char PY_mb_xiu   []={"ĞŞĞâĞåĞİĞßËŞĞáĞäĞãĞà³ôßİá¶âÊâÓäåğ¼õ÷÷Û"};
const unsigned char PY_mb_xu    []={"ĞíĞëĞèĞéĞêĞîĞøĞòĞğĞóĞõĞöĞçĞìĞñĞ÷ÓõĞïĞôĞæôÚÛÃèòä°Ş£çïÛ×äªñãõ¯Ú¼äÓìãíìí¹"};
const unsigned char PY_mb_xuan  []={"Ñ¡ĞüĞıĞşĞûĞúĞùÑ¤Ñ£Ñ¢È¯ÙØìÅÚÎİæŞïãùäÖäöè¯é¸êÑìÓíÛîçïàğç"};
const unsigned char PY_mb_xue   []={"Ñ§Ñ©ÑªÑ¥Ñ¨Ï÷Ñ¦õ½àå÷¨í´"};
const unsigned char PY_mb_xun   []={"Ñ°Ñ¶Ñ¬ÑµÑ­Ñ³Ñ®Ñ²Ñ¸Ñ±Ñ´Ñ·Ñ«»çÑ¯¿£ÙãÛ÷Ü÷Ş¦Ş¹á¾áßâ´âşä­ä±êÖõ¸öàÛ¨ñ¿"};
const unsigned char PY_mb_ya    []={"Ñ½Ñ¹ÑÀÑºÑ¿Ñ¼ÔşÑÂÑÆÑÇÑÄÑ¾ÑÅÑÃÑ»ÑÈÑÁØóÛëŞëá¬åÂæ«çğèâë²í¼íığéñâ"};
const unsigned char PY_mb_yan   []={"ÑÛÑÌÑØÑÎÑÔÑİÑÏÑÊÑÍÑ×ÑÚÑáÑçÑÒÑĞÑÓÑßÑéÑŞÑËÑâÑãÑäÑåÑæÑÑÑÜÑèÑàÑÕÑÖÑÉÑÙØÉİÎ÷ÊçüäÙìÍóÛØÍÙğâûéÜäÎÚİÙÈëÙêÌãÆÙ²Û±Û³åûáÃæÌî»õ¦÷Ğ÷úÇ¦ÒóÚçÜ¾ãÕëçØß"};
const unsigned char PY_mb_yang  []={"ÑùÑøÑòÑóÑöÑïÑíÑõÑ÷ÑîÑúÑôÑêÑëÑìÑğÑñì¾í¦áà÷±ãóòÕìÈâó"};
const unsigned char PY_mb_yao   []={"ÒªÒ¡Ò©Ò§ÑüÒ¤Ò¨ÑûÑıÒ¥Ò£Ò¦ÑşÒ«Ò¢Ô¿½ÄØ²Ø³ßºáÊáæçÛçòèÃé÷ê×ëÈğÎñº÷¥Å±ÌÕÔ¼ï¢"};
const unsigned char PY_mb_ye    []={"Ò²Ò¹ÒµÒ°Ò¶Ò¯Ò³ÒºÒ´Ò¸Ò±Ò­Ò®ÑÊÒ·Ò¬Ğ°ÚËÚşêÊìÇŞŞîôØÌ"};
const unsigned char PY_mb_yi    []={"Ò»ÒÔÒÑÒÚÒÂÒÆÒÀÒ×Ò½ÒÒÒÇÒàÒÎÒæÒĞÒÌÒíÒëÒÁÉßÒÅÊ³°¬ÒÈÒÉÒÊÒËÒìÒÍÒ¼ÒÏÒêÒ¾Ò¿ÒÓÒîÒÕÒÖÒïÒØ¶êÒÙÎ²ÒÛÒÜÒİÒŞÒßÒÃÒáÒâÒãÒäÒåÒÄÒçÒèÒéâøğêï×ñ¯âùæäì½ìÚôıñ´ì¥á»ÛİéìàÉß×Ü²àæØæÚ±âÂäôØıßŞğùâ¢íôôàŞÄÜÓÜèØîÙ«êİîÆçËåÆØ×ã¨÷ğôèß®ŞÈòæÛüŞÚáÚŞ²ß½éóïî"};
const unsigned char PY_mb_yin   []={"ÒòÒıÓ¡ÒøÒôÒûÒõÒşÒñÒ÷ÒüÒúÒğÒùÒóÒöÑÌÜ§Û´à³â¹Ø·ö¸ßÅÛßáşÛóö¯ò¾ë³î÷ñ¿ñ«ä¦Üá"};
const unsigned char PY_mb_ying  []={"Ó¦Ó²Ó°ÓªÓ­Ó³Ó¬Ó®Ó¥Ó¢Ó±Ó¨Ó¯Ó¤Ó£Ó§Ó«Ó©İÓéºİöñ¨ÜãğĞëôİºè¬Û«àÓŞüçøäŞäëÙøó¿å­âßÜşò£"};
const unsigned char PY_mb_yo    []={"Ó´Óıà¡"};
const unsigned char PY_mb_yong  []={"ÓÃÓ¿ÓÀÓµÓ¼ÓÂÓºÓ½Ó¾Ó¶Ó»Ó¸Ó¹Ó·ÓÁÙ¸ÛÕÜ­à¯ã¼çßïŞğ®÷«÷Ó"};
const unsigned char PY_mb_you   []={"ÓĞÓÖÓÉÓÒÓÍÓÎÓ×ÓÅÓÑÓËÓÇÓÈÓÌÓÕÓÆÓÊÓÏÓÓÓÄÓÔØüØÕÙ§İ¬İ¯İµßÏàóå¶èÖéàë»îğğàòÄòÊòööÏ÷î÷øòøôí"};
const unsigned char PY_mb_yu    []={"ÓëÓÚÓûÓãÓêÓàÓöÓïÓúÓüÓñÓæÓèÓşÓıÓŞÓğÓİÓéÓÙÓßÓìÓíÓîÓØÓáÓâÓòÓóÓô¹ÈÓõÓÛÓ÷ÓøÓùÓäÖàÓåÎ¾ÓÜÓçÔ¡Ô¢Ô£Ô¤Ô¥Ô¦ÎµåıáÎö§âÅãĞñ¾ğÁæ¥ŞíñÁêìô§ô¨ö¹İ÷ìÏîÚÚÄæúì¶óÄè¤Ø®í²ì£Ù¶ØñàôğÖâ×êÅİÇğõÚÍå÷àöğöìÙâÀØ¹ìÛëéáüİÒòâòõ"};
const unsigned char PY_mb_yuan  []={"Ô¶Ô±ÔªÔºÔ²Ô­Ô¸Ô°Ô®Ô³Ô¹Ô©Ô´ÔµÔ¬Ô¨Ô·Ô«Ô§Ô¯à÷ö½éÚæÂë¼íóğ°ŞòÜ¾ãäè¥ó¢óîÜ«Ûù"};
const unsigned char PY_mb_yue   []={"ÔÂÔ½Ô¼Ô¾ÔÄÀÖÔÀÔÃÔ»ËµÔÁÔ¿å®îáë¾ÙßèİéĞ"};
const unsigned char PY_mb_yun   []={"ÔÆÔËÔÎÔÊÔÈÔÏÔÉÔĞÔÅÔÌÔÍÔÇÔ±ìÙëµã¢ã³Û©Ü¿óŞè¹êÀáñéæç¡"};
const unsigned char PY_mb_za    []={"ÔÓÔÒÕ¦ÔÑÔúÔÛßÆŞÙ"};
const unsigned char PY_mb_zai   []={"ÔÚÔÙÔÖÔØÔÔÔ×ÔÕáÌçŞ×Ğ"};
const unsigned char PY_mb_zan   []={"ÔÛÔİÔÜÔŞô¢ôõôØè¶ŞÙêÃöÉ"};
const unsigned char PY_mb_zang  []={"ÔàÔáÔß²Øê°æàŞÊ"};
const unsigned char PY_mb_zao   []={"ÔçÔìÔâÔãÔîÔïÔæÔäÔêÔåÔíÔëÔèÔéßğ"};
const unsigned char PY_mb_ze    []={"ÔòÔğÔñÔóÕ¦²àóåô·àıåÅßõØÆê¾óĞØÓ"};
const unsigned char PY_mb_zei   []={"Ôô"};
const unsigned char PY_mb_zen   []={"ÔõÚÚ"};
const unsigned char PY_mb_zeng  []={"ÔöÔùÔ÷Ôø×ÛçÕîÀêµï­"};
const unsigned char PY_mb_zha   []={"ÔúÕ¨ÔüÕ¢Õ£Õ¥Õ§ÔşÕ©ÔûÔıÕ¡Şêß¸ßåßîâªíÄğäòÆ÷ş²éÀ¯Õ¤Õ¦à©é«×õ"};
const unsigned char PY_mb_zhai  []={"ÕªÕ­Õ®Õ«Õ¯ÔñµÔÕ¬²à¼ÀíÎñ©"};
const unsigned char PY_mb_zhan  []={"Õ¾Õ¼Õ½ÕµÕ´Õ³Õ±Õ¹Õ»Õ²²üÕºÕ¿ÕÀÕ¶Õ·Õ¸Õ°ÚŞŞøì¹"};
const unsigned char PY_mb_zhang []={"ÕÅÕÂ³¤ÕÊÕÌÕÉÕÆÕÇÕËÕÁÕÈÕÃÕÄÕÍÕÎÕÏØëæÑá¤Ûµè°áÖâ¯ó¯"};
const unsigned char PY_mb_zhao  []={"ÕÒ×ÅÕÕÕĞÕÖ×¦Õ×³¯ÕÑÕÓÕØ³°ÕÙÕÔèşîÈóÉÚ¯ßú"};
const unsigned char PY_mb_zhe   []={"×ÅÕâÕßÕÛÕÚÕİÕÜÕáÕàÕŞÕãèÏéüô÷ß¡ğÑíİñŞòØÚØ"};
const unsigned char PY_mb_zhen  []={"ÕæÕóÕòÕëÕğÕíÕñÕåÕäÕîÕïÕçÕèÕéÕêÕìçÇİèìõóğéôé»ğ¡êâëŞğ²ëÓä¥èåî³ÛÚé©"};
const unsigned char PY_mb_zheng []={"ÕıÕûÕöÕùÕõÕ÷ÕúÖ¤Ö¢Ö£ÕüÕôÕøÕşÖ¡á¿îÛï£óİÚºáç¶¡öë"};
const unsigned char PY_mb_zhi   []={"Ö»Ö®Ö±ÖªÖÆÖ¸Ö½Ö§Ö¥Ö¦ÖÉÖ¨Ö©ÖÊÖ«Ö¬Ö­ÖËÖ¯Ö°ÖÌÖ²µÖÖ³Ö´ÖµÖ¶Ö·ÖÇÖÍÖ¹ÖºÖÎÖ¼ÖÏÖ¾Ö¿ÖÀÖÁÖÂÖÃÖÄÊ¶ÖÅÊÏÖÈàùŞıíéèäè×éòâåìíòÎëùö£Û¤èÙåéÜÆìóåëğºôêõÙëÕæïéùğëÚìõÜïôÛúêŞØ´õ¥õôõÅèÎ¼¿"};
const unsigned char PY_mb_zhong []={"ÖĞÖØÖÖÖÓÖ×ÖÚÖÕÖÑÖÒÖÙÖÔõàô±ó®ïñÚ£âì"};
const unsigned char PY_mb_zhou  []={"ÖÜÖŞÖåÖàÖİÖáÖÛÖçÖèÖæÖßÖâÖãÖäôíëĞæûİ§ßúíØç§ô¦æ¨ôü"};
const unsigned char PY_mb_zhu   []={"×¡Ö÷ÖíÖñÖêÖóÖşÖøÖéÖëÖìÖîÖïÖğÖòÖôÖõÖöÖùÖúÖûÖüÖı×¢×£×¤Øùäóä¨ğñôãÜïÜÑéÍô¶èÌóçìÄÙªîùğæä¾ñÒõî÷æÛ¥éÆóÃÊôÊõ"};
const unsigned char PY_mb_zhua  []={"×¥×¦ÎÎ"};
const unsigned char PY_mb_zhuai []={"×§×ª"};
const unsigned char PY_mb_zhuan []={"×ª×¨×©×¬´«×«×­ò§âÍßùãç"};
const unsigned char PY_mb_zhuang[]={"×°×²×¯×³×®×´´±×±Ù×ŞÊí°"};
const unsigned char PY_mb_zhui  []={"×·×¹×º×¶×¸×µæíã·çÄö¿"};
const unsigned char PY_mb_zhun  []={"×¼×»ÍÍëÆñ¸"};
const unsigned char PY_mb_zhuo  []={"×½×À×Å×Ä×¾×Æ×Ç×¿×Á½É×Â×ÃßªìÌåªÚÂä·äÃÙ¾ïíìúí½"};
const unsigned char PY_mb_zi    []={"×Ö×Ô×Ó×Ï×Ñ×Ê×ËÖ¨×Ò×Ğ×É×Î×Õ×Ì×ÍÚÑÜëáÑæ¢æÜç»è÷ê¢êßí§íöïÅïöñèóÊôÒôôö¤ö·öö÷Ú×Èõş"};
const unsigned char PY_mb_zong  []={"×Ü×İ×Ú×Ø×Û×Ù××ÙÌôÕèÈëê"};
const unsigned char PY_mb_zou   []={"×ß×á×à×ŞöíÛ¸ÚîæãÚÁ"};
const unsigned char PY_mb_zu    []={"×é×å×ã×è×â×æ×çİÏïß×äÙŞ"};
const unsigned char PY_mb_zuan  []={"×ê×ë×¬ß¬çÚõò"};
const unsigned char PY_mb_zui   []={"×î×ì×í×ï¶Ñ¾×õşŞ©"};
const unsigned char PY_mb_zun   []={"×ğ×ñß¤é×÷®"};
const unsigned char PY_mb_zuo   []={"×ö×÷×ø×ó×ù×òÔä×ôÚèßòâôëÑìñ´é×ÁàÜóĞõ¡×õ"};
const unsigned char PY_mb_bd    []={",.?!:;'\"()<>[]{}$%@*+-_=~`|/\\^&*"};
const unsigned char PY_mb_sz    []={"0123456789"}; //Êı×Ö
const unsigned char PY_mb_abc   []={"abc"};
const unsigned char PY_mb_def   []={"def"};
const unsigned char PY_mb_ghi   []={"ghi"};
const unsigned char PY_mb_jkl   []={"jkl"}; 
const unsigned char PY_mb_mno   []={"mno"};
const unsigned char PY_mb_pqrs  []={"pqrs"}; 
const unsigned char PY_mb_tuv   []={"tuv"};
const unsigned char PY_mb_wxyz  []={"wxyz"}; 
const unsigned char PY_mb_ABC   []={"ABC"};
const unsigned char PY_mb_DEF   []={"DEF"};
const unsigned char PY_mb_GHI   []={"GHI"};
const unsigned char PY_mb_JKL   []={"JKL"}; 
const unsigned char PY_mb_MNO   []={"MNO"};
const unsigned char PY_mb_PQRS  []={"PQRS"}; 
const unsigned char PY_mb_TUV   []={"TUV"};
const unsigned char PY_mb_WXYZ  []={"WXYZ"};

const struct t9PY_index  t9PY_index0[] ={0x00," ",PY_mb_bd};		
//1
const struct t9PY_index  t9PY_index1[] ={0x20," ",PY_mb_space};	//1


const struct t9PY_index  t9PY_index2[] ={{0x2,"a",PY_mb_a},	   //55
{0x22,"ba",PY_mb_ba},
{0x22,"ca",PY_mb_ca},
{0x224,"bai",PY_mb_bai},
{0x224,"cai",PY_mb_cai},
{0x226,"ban",PY_mb_ban},
{0x226,"bao",PY_mb_bao},
{0x226,"can",PY_mb_can},
{0x226,"cao",PY_mb_cao},
{0x226,"cen",PY_mb_cen},
{0x2264,"bang",PY_mb_bang},
{0x2264,"cang",PY_mb_cang},
{0x23,"ce",PY_mb_ce},
{0x234,"bei",PY_mb_bei},
{0x236,"ben",PY_mb_ben},
{0x2364,"beng",PY_mb_beng},
{0x2364,"ceng",PY_mb_ceng},
{0x24,"ai",PY_mb_ai},
{0x24,"bi",PY_mb_bi},
{0x24,"ci",PY_mb_ci},
{0x242,"cha",PY_mb_cha},
{0x2424,"chai",PY_mb_chai},
{0x2426,"bian",PY_mb_bian},
{0x2426,"biao",PY_mb_biao},
{0x2426,"chan",PY_mb_chan},
{0x2426,"chao",PY_mb_chao},
{0x24264,"chang",PY_mb_chang},
{0x243,"bie",PY_mb_bie},
{0x243,"che",PY_mb_che},
{0x2436,"chen",PY_mb_chen},
{0x24364,"cheng",PY_mb_cheng},
{0x244,"chi",PY_mb_chi},
{0x246,"bin",PY_mb_bin},
{0x2464,"bing",PY_mb_bing},
{0x24664,"chong",PY_mb_chong},
{0x2468,"chou",PY_mb_chou},
{0x248,"chu",PY_mb_chu},
{0x24824,"chuai",PY_mb_chuai},
{0x24826,"chuan",PY_mb_chuan},
{0x248264,"chuang",PY_mb_chuang},
{0x2484,"chui",PY_mb_chui},
{0x2484,"chun",PY_mb_chun},
{0x2486,"chuo",PY_mb_chuo},										
{0x26,"an",PY_mb_an},
{0x26,"ao",PY_mb_ao},                   	
{0x26,"bo",PY_mb_bo},
{0x264,"ang",PY_mb_ang},
{0x2664,"cong",PY_mb_cong},
{0x268,"cou",PY_mb_cou},
{0x28,"bu",PY_mb_bu},
{0x28,"cu",PY_mb_cu},
{0x2826,"cuan",PY_mb_cuan},
{0x284,"cui",PY_mb_cui},
{0x286,"cun",PY_mb_cun},
{0x286,"cuo",PY_mb_cuo}	
};	 
const struct t9PY_index  t9PY_index3[] ={{0x03,"e",PY_mb_e},		//33
{0x32,"da",PY_mb_da},
{0x32,"fa",PY_mb_fa},
{0x324,"dai",PY_mb_dai},
{0x326,"dan",PY_mb_dan},
{0x326,"dao",PY_mb_dao},
{0x326,"fan",PY_mb_fan}, 
{0x3264,"dang",PY_mb_dang},
{0x3264,"fang",PY_mb_fang},										 
{0x33,"de",PY_mb_de},
{0x334,"fei",PY_mb_fei},
{0x336,"fen",PY_mb_fen},
{0x3364,"deng",PY_mb_deng},
{0x3364,"feng",PY_mb_feng},
{0x34,"di",PY_mb_di},
{0x342,"dia",PY_mb_dia},
{0x3426,"dian",PY_mb_dian},
{0x3426,"diao",PY_mb_diao},
{0x343,"die",PY_mb_die},
{0x3464,"ding",PY_mb_ding},
{0x348,"diu",PY_mb_diu},
{0x36,"en",PY_mb_en},
{0x36,"fo",PY_mb_fo},
{0x3664,"dong",PY_mb_dong},
{0x368,"dou",PY_mb_dou},
{0x368,"fou",PY_mb_fou},										 
{0x37,"er",PY_mb_er},
{0x38,"du",PY_mb_du},
{0x38,"fu",PY_mb_fu},
{0x3826,"duan",PY_mb_duan},
{0x384,"dui",PY_mb_dui},
{0x386,"dun",PY_mb_dun},
{0x386,"duo",PY_mb_duo}                                         
};
const struct t9PY_index  t9PY_index4[] ={{0x42,"ha",PY_mb_ha},	   //38
{0x42,"ga",PY_mb_ga},
{0x423,"hai",PY_mb_hai},
{0x424,"gai",PY_mb_gai},
{0x426,"gan",PY_mb_gan},
{0x426,"gao",PY_mb_gao},
{0x426,"han",PY_mb_han},
{0x426,"hao",PY_mb_hao}, 
{0x4264,"gang",PY_mb_gang},
{0x4264,"hang",PY_mb_hang},
{0x43,"ge",PY_mb_ge},
{0x43,"he",PY_mb_he},
{0x434,"gei",PY_mb_gei},
{0x434,"hei",PY_mb_hei},
{0x436,"gen",PY_mb_gan},
{0x436,"hen",PY_mb_hen},
{0x4364,"geng",PY_mb_geng},
{0x4364,"heng",PY_mb_heng},
{0x4664,"gong",PY_mb_gong},
{0x4664,"hong",PY_mb_hong},
{0x468,"gou",PY_mb_gou},
{0x468,"hou",PY_mb_hou},
{0x48,"gu",PY_mb_gu},
{0x48,"hu",PY_mb_hu},
{0x482,"gua",PY_mb_gua},
{0x482,"hua",PY_mb_hua},
{0x4823,"huai",PY_mb_huai},
{0x4824,"guai",PY_mb_guai},                                         
{0x4826,"guan",PY_mb_guan},
{0x4826,"huan",PY_mb_huan},
{0x48264,"guang",PY_mb_guang},
{0x48264,"huang",PY_mb_huang},
{0x484,"gui",PY_mb_gui},
{0x484,"hui",PY_mb_hui},
{0x486,"gun",PY_mb_gun},
{0x486,"guo",PY_mb_guo},
{0x486,"hun",PY_mb_hun},
{0x486,"huo",PY_mb_huo}
};
const struct t9PY_index  t9PY_index5[] ={{0x52,"ka",PY_mb_ka},	  	//57
{0x52,"la",PY_mb_la},
{0x524,"kai",PY_mb_kai},
{0x524,"lai",PY_mb_lai},                                         
{0x526,"kan",PY_mb_kan},
{0x526,"kao",PY_mb_kao},
{0x526,"lan",PY_mb_lan},
{0x526,"lao",PY_mb_lao},
{0x5264,"kang",PY_mb_kang},
{0x5264,"lang",PY_mb_lang},
{0x53,"ke",PY_mb_ke},
{0x53,"le",PY_mb_le},
{0x534,"lei",PY_mb_lei},
{0x536,"ken",PY_mb_ken},
{0x5364,"keng",PY_mb_keng},
{0x5366,"leng",PY_mb_leng}, 
{0x54,"ji",PY_mb_ji},
{0x54,"li",PY_mb_li},
{0x542,"jia",PY_mb_jia},
{0x542,"lia",PY_mb_lia},
{0x5426,"jian",PY_mb_jian},
{0x5426,"jiao",PY_mb_jiao},
{0x5426,"lian",PY_mb_lian},
{0x5426,"liao",PY_mb_liao},
{0x54264,"jiang",PY_mb_jiang},
{0x54264,"liang",PY_mb_liang},									     
{0x543,"jie",PY_mb_jie},
{0x543,"lie",PY_mb_lie},
{0x546,"jin",PY_mb_jin},
{0x546,"lin",PY_mb_lin},
{0x5464,"jing",PY_mb_jing},
{0x5464,"ling",PY_mb_ling},
{0x54664,"jiong",PY_mb_jiong},
{0x548,"jiu",PY_mb_jiu},
{0x548,"liu",PY_mb_liu},
{0x5664,"kong",PY_mb_kong},
{0x5664,"long",PY_mb_long},
{0x568,"kou",PY_mb_kou},
{0x568,"lou",PY_mb_lou},										 
{0x58,"ju",PY_mb_ju},
{0x58,"ku",PY_mb_ku},
{0x58,"lu",PY_mb_lu},
{0x58,"lv",PY_mb_lv},									     
{0x582,"kua",PY_mb_kua},
{0x5824,"kuai",PY_mb_kuai},
{0x5826,"juan",PY_mb_juan},
{0x5826,"kuan",PY_mb_kuan},
{0x5826,"luan",PY_mb_luan},									                                         
{0x58264,"kuang",PY_mb_kuang},
{0x583,"jue",PY_mb_jue},
{0x583,"lue",PY_mb_lue},
{0x584,"kui",PY_mb_kui},	
{0x586,"jun",PY_mb_jun},
{0x586,"kun",PY_mb_kun},
{0x586,"kuo",PY_mb_kuo},
{0x586,"lun",PY_mb_lun},
{0x586,"luo",PY_mb_luo}
};
const struct t9PY_index  t9PY_index6[] ={{0x06,"o",PY_mb_o},	   //44
{0x62,"ma",PY_mb_ma},
{0x62,"na",PY_mb_na},
{0x624,"mai",PY_mb_mai},
{0x624,"nai",PY_mb_nai},
{0x626,"man",PY_mb_man},
{0x626,"mao",PY_mb_mao},
{0x626,"nan",PY_mb_nan},
{0x626,"nao",PY_mb_nao},
{0x6264,"mang",PY_mb_mang},
{0x6264,"nang",PY_mb_nang},										 
{0x63,"me",PY_mb_me},
{0x63,"ne",PY_mb_ne},
{0x634,"mei",PY_mb_mei},
{0x634,"nei",PY_mb_nei},                                    
{0x636,"men",PY_mb_men},
{0x636,"nen",PY_mb_nen},
{0x6364,"meng",PY_mb_meng},
{0x6364,"neng",PY_mb_neng},
{0x64,"mi",PY_mb_mi},
{0x64,"ni",PY_mb_ni},
{0x6426,"mian",PY_mb_mian},
{0x6426,"miao",PY_mb_miao},
{0x6426,"nian",PY_mb_nian},
{0x6426,"niao",PY_mb_niao},									     
{0x64264,"niang",PY_mb_niang},
{0x643,"mie",PY_mb_mie},
{0x643,"nie",PY_mb_nie},
{0x646,"min",PY_mb_min},
{0x646,"nin",PY_mb_nin},
{0x6464,"ming",PY_mb_ming},
{0x6464,"ning",PY_mb_ning},
{0x648,"miu",PY_mb_miu},
{0x648,"niu",PY_mb_niu},										 
{0x66,"mo",PY_mb_mo},
{0x6664,"nong",PY_mb_nong},
{0x668,"mou",PY_mb_mou},
{0x68,"mu",PY_mb_mu},
{0x68,"nu",PY_mb_nu},
{0x68,"nv",PY_mb_nv},
{0x68,"ou",PY_mb_ou},
{0x6826,"nuan",PY_mb_nuan},
{0x683,"nue",PY_mb_nue},
{0x686,"nuo",PY_mb_nuo}                                         
};
const struct t9PY_index  t9PY_index7[] ={{0x72,"pa",PY_mb_pa},		 //79
{0x72,"sa",PY_mb_sa},
{0x724,"pai",PY_mb_pai},
{0x724,"sai",PY_mb_sai},
{0x726,"pan",PY_mb_pan},
{0x726,"pao",PY_mb_pao},
{0x726,"ran",PY_mb_ran},
{0x726,"rao",PY_mb_rao},
{0x726,"sao",PY_mb_sao},
{0x726,"san",PY_mb_san},
{0x7264,"pang",PY_mb_pang},
{0x7264,"rang",PY_mb_rang},
{0x7264,"sang",PY_mb_sang},
{0x73,"re",PY_mb_re},
{0x73,"se",PY_mb_se},
{0x734,"pei",PY_mb_pei},
{0x736,"pen",PY_mb_pen},
{0x736,"ren",PY_mb_ren},
{0x736,"sen",PY_mb_sen},
{0x7364,"peng",PY_mb_peng},
{0x7364,"reng",PY_mb_reng},
{0x7364,"seng",PY_mb_seng},
{0x74,"pi",PY_mb_pi},
{0x74,"qi",PY_mb_qi},
{0x74,"ri",PY_mb_ri},
{0x74,"si",PY_mb_si},
{0x742,"sha",PY_mb_sha},
{0x742,"qia",PY_mb_qia},
{0x7424,"shai",PY_mb_shai},
{0x7426,"pian",PY_mb_pian},
{0x7426,"piao",PY_mb_piao},
{0x7426,"qian",PY_mb_qian},
{0x7426,"qiao",PY_mb_qiao},
{0x7426,"shan",PY_mb_shan},
{0x7426,"shao",PY_mb_shao},
{0x74264,"qiang",PY_mb_qiang},
{0x74264,"shang",PY_mb_shang},
{0x743,"qie",PY_mb_qie},
{0x743,"pie",PY_mb_pie},
{0x743,"she",PY_mb_she},
{0x7436,"shen",PY_mb_shen},
{0x74364,"sheng",PY_mb_sheng},
{0x744,"shi",PY_mb_shi},								
{0x746,"pin",PY_mb_pin},
{0x746,"qin",PY_mb_qin},
{0x7464,"ping",PY_mb_ping},                                   
{0x7464,"qing",PY_mb_qing},
{0x74664,"qiong",PY_mb_qiong},
{0x7468,"shou",PY_mb_shou},
{0x748,"qiu",PY_mb_qiu},
{0x748,"shu",PY_mb_shu},
{0x7482,"shua",PY_mb_shua},
{0x74824,"shuai",PY_mb_shuai},
{0x74826,"shuan",PY_mb_shuan},
{0x748264,"shuang",PY_mb_shuang},
{0x7484,"shui",PY_mb_shui},
{0x7486,"shun",PY_mb_shun},
{0x7486,"shuo",PY_mb_shuo},
{0x76,"po",PY_mb_po},
{0x7664,"rong",PY_mb_rong},
{0x7664,"song",PY_mb_song},
{0x768,"pou",PY_mb_pou},                                         
{0x768,"rou",PY_mb_rou},
{0x768,"sou",PY_mb_sou},
{0x78,"pu",PY_mb_pu},
{0x78,"qu",PY_mb_qu},
{0x78,"ru",PY_mb_ru},
{0x78,"su",PY_mb_su},
{0x7826,"quan",PY_mb_quan},
{0x7826,"ruan",PY_mb_ruan},
{0x7826,"suan",PY_mb_suan},
{0x783,"que",PY_mb_que},
{0x784,"rui",PY_mb_rui},
{0x784,"sui",PY_mb_sui},									
{0x786,"qun",PY_mb_qun},
{0x786,"run",PY_mb_run},
{0x786,"ruo",PY_mb_ruo},
{0x786,"sun",PY_mb_sun},
{0x786,"suo",PY_mb_suo}                                   
};
const struct t9PY_index  t9PY_index8[] ={{0x82,"ta",PY_mb_ta},	 //19
{0x824,"tai",PY_mb_tai},
{0x826,"tan",PY_mb_tan},                                         
{0x826,"tao",PY_mb_tao},
{0x8264,"tang",PY_mb_tang},
{0x83,"te",PY_mb_te},
{0x8364,"teng",PY_mb_teng},
{0x84,"ti",PY_mb_ti},
{0x8426,"tian",PY_mb_tian},
{0x8426,"tiao",PY_mb_tiao},
{0x843,"tie",PY_mb_tie},
{0x8464,"ting",PY_mb_ting},
{0x8664,"tong",PY_mb_tong},
{0x868,"tou",PY_mb_tou},
{0x88,"tu",PY_mb_tu},
{0x8826,"tuan",PY_mb_tuan},
{0x884,"tui",PY_mb_tui},
{0x886,"tun",PY_mb_tun},
{0x886,"tuo",PY_mb_tuo}                                         
};
const struct t9PY_index  t9PY_index9[] ={{0x92,"wa",PY_mb_wa},	  //74
{0x92,"ya",PY_mb_ya},
{0x92,"za",PY_mb_za},
{0x924,"wai",PY_mb_wai},
{0x924,"zai",PY_mb_zai},
{0x926,"wan",PY_mb_wan},
{0x926,"yan",PY_mb_yan},
{0x926,"yao",PY_mb_yao},
{0x926,"zan",PY_mb_zan},
{0x926,"zao",PY_mb_zao},
{0x9264,"wang",PY_mb_wang},
{0x9264,"yang",PY_mb_yang},
{0x9264,"zang",PY_mb_zang},
{0x93,"ye",PY_mb_ye},
{0x93,"ze",PY_mb_ze},
{0x934,"wei",PY_mb_wei},
{0x934,"zei",PY_mb_zei},
{0x936,"wen",PY_mb_wen},
{0x936,"zen",PY_mb_zen},
{0x9364,"weng",PY_mb_weng},
{0x9364,"zeng",PY_mb_zeng},
{0x94,"xi",PY_mb_xi},
{0x94,"yi",PY_mb_yi},
{0x94,"zi",PY_mb_zi},
{0x942,"xia",PY_mb_xia},
{0x942,"zha",PY_mb_zha},
{0x9424,"zhai",PY_mb_zhai},
{0x9426,"xian",PY_mb_xian},
{0x9426,"xiao",PY_mb_xiao},
{0x9426,"zhan",PY_mb_zhan},
{0x9426,"zhao",PY_mb_zhao},
{0x94264,"xiang",PY_mb_xiang},
{0x94264,"zhang",PY_mb_zhang},
{0x943,"xie",PY_mb_xie},
{0x943,"zhe",PY_mb_zhe},
{0x9436,"zhen",PY_mb_zhen},
{0x94364,"zheng",PY_mb_zheng},
{0x944,"zhi",PY_mb_zhi},
{0x946,"xin",PY_mb_xin},
{0x946,"yin",PY_mb_yin},
{0x9464,"xing",PY_mb_xing},
{0x9464,"ying",PY_mb_ying},
{0x94664,"xiong",PY_mb_xiong},
{0x94664,"zhong",PY_mb_zhong},
{0x9468,"zhou",PY_mb_zhou},
{0x948,"xiu",PY_mb_xiu},
{0x948,"zhu",PY_mb_zhu},
{0x9482,"zhua",PY_mb_zhua},
{0x94824,"zhuai",PY_mb_zhuai},
{0x94826,"zhuan",PY_mb_zhuan},
{0x948264,"zhuang",PY_mb_zhuang},
{0x9484,"zhui",PY_mb_zhui},
{0x9486,"zhun",PY_mb_zhun},
{0x9486,"zhuo",PY_mb_zhuo},
{0x96,"wo",PY_mb_wo},
{0x96,"yo",PY_mb_yo},
{0x9664,"yong",PY_mb_yong},
{0x9664,"zong",PY_mb_zong},
{0x968,"you",PY_mb_you},
{0x968,"zou",PY_mb_zou},
{0x98,"wu",PY_mb_wu},
{0x98,"xu",PY_mb_xu},
{0x98,"yu",PY_mb_yu},
{0x98,"zu",PY_mb_zu},									
{0x9826,"xuan",PY_mb_xuan},
{0x9826,"yuan",PY_mb_yuan},
{0x9826,"zuan",PY_mb_zuan},
{0x983,"xue",PY_mb_xue},
{0x983,"yue",PY_mb_yue},
{0x984,"zui",PY_mb_zui},
{0x986,"xun",PY_mb_xun},
{0x986,"yun",PY_mb_yun},
{0x986,"zun",PY_mb_zun},
{0x986,"zuo",PY_mb_zuo}
};


const struct t9PY_index  t9PY_sz[] ={{0x00,"0",&PY_mb_sz[0]},
{0x01,"1",&PY_mb_sz[1]},
{0x02,"2",&PY_mb_sz[2]},
{0x03,"3",&PY_mb_sz[3]},
{0x04,"4",&PY_mb_sz[4]},
{0x05,"5",&PY_mb_sz[5]},
{0x06,"6",&PY_mb_sz[6]},
{0x07,"7",&PY_mb_sz[7]},
{0x08,"8",&PY_mb_sz[8]},
{0x09,"9",&PY_mb_sz[9]}
}; 
const struct t9PY_index  t9PY_abc[] ={{0x00,"",PY_mb_space},
{0x01,"",PY_mb_space},
{0x02,"abc",PY_mb_abc},
{0x03,"def",PY_mb_def},
{0x04,"ghi",PY_mb_ghi},
{0x05,"jkl",PY_mb_jkl},
{0x06,"mno",PY_mb_mno},
{0x07,"pqrs",PY_mb_pqrs},
{0x08,"tuv",PY_mb_tuv},
{0x09,"wxyz",PY_mb_wxyz}	  								 
};
const struct t9PY_index  t9PY_ABC[] ={{0x00,"",PY_mb_space},
{0x01,"",PY_mb_space},
{0x02,"ABC",PY_mb_ABC},
{0x03,"DEF",PY_mb_DEF},
{0x04,"GHI",PY_mb_GHI},
{0x05,"JKL",PY_mb_JKL},
{0x06,"MNO",PY_mb_MNO},
{0x07,"PQRS",PY_mb_PQRS},
{0x08,"TUV",PY_mb_TUV},
{0x09,"WXYZ",PY_mb_WXYZ}	  								 
};
const struct t9PY_index  *t9PY_index_headno[]={t9PY_index0,
t9PY_index1,
t9PY_index2,
t9PY_index3,
t9PY_index4,
t9PY_index5,
t9PY_index6,
t9PY_index7,
t9PY_index8,
t9PY_index9};

#endif
