/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 00:21:23 by bmickael          #+#    #+#             */
/*   Updated: 2017/11/22 00:23:56 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATON_H
# define AUTOMATON_H
#include "libft.h"

# ifndef PARSER_ERROR
#  define PARSER_REOPEN 2
# endif
# ifndef PARSER_ERROR
#  define PARSER_ERROR 1
# endif
# ifndef PARSER_SUCCESS
#  define PARSER_SUCCESS 0
# endif

# ifndef FIRST_REDUCE_RULE
#  define FIRST_REDUCE_RULE 4242
# endif
enum shift {
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	s8,
	s9,
	s10,
	s11,
	s12,
	s13,
	s14,
	s15,
	s16,
	s17,
	s18,
	s19,
	s20,
	s21,
	s22,
	s23,
	s24,
	s25,
	s26,
	s27,
	s28,
	s29,
	s30,
	s31,
	s32,
	s33,
	s34,
	s35,
	s36,
	s37,
	s38,
	s39,
	s40,
	s41,
	s42,
	s43,
	s44,
	s45,
	s46,
	s47,
	s48,
	s49,
	s50,
	s51,
	s52,
	s53,
	s54,
	s55,
	s56,
	s57,
	s58,
	s59,
	s60,
	s61,
	s62,
	s63,
	s64,
	s65,
	s66,
	s67,
	s68,
	s69,
	s70,
	s71,
	s72,
	s73,
	s74,
	s75,
	s76,
	s77,
	s78,
	s79,
	s80,
	s81,
	s82,
	s83,
	s84,
	s85,
	s86,
	s87,
	s88,
	s89,
	s90,
	s91,
	s92,
	s93,
	s94,
	s95,
	s96,
	s97,
	s98,
	s99,
	s100,
	s101,
	s102,
	s103,
	s104,
	s105,
	s106,
	s107,
	s108,
	s109,
	s110,
	s111,
	s112,
	s113,
	s114,
	s115,
	s116,
	s117,
	s118,
	s119,
	s120,
	s121,
	s122,
	s123,
	s124,
	s125,
	s126,
	s127,
	s128,
	s129,
	s130,
	s131,
	s132,
	s133,
	s134,
	s135,
	s136,
	s137,
	s138,
	s139,
	s140,
	s141,
	s142,
	s143,
	s144,
	s145,
	s146,
	s147,
	s148,
	s149,
	s150,
	s151,
	s152,
	s153,
	s154,
	s155,
	s156,
	s157,
	s158,
	s159,
	s160,
	s161,
	s162,
	s163,
	s164,
	s165,
	s166,
	s167,
	s168,
	s169,
	s170,
	s171,
	s172,
	s173,
	s174,
	s175,
	s176,
	s177,
	s178,
	s179,
	s180,
	s181,
	s182,
	s183,
	s184,
	s185,
	s186,
	s187,
	s188,
	s189,
	s190,
	s191,
	s192,
	s193,
	s194,
	s195,
	s196,
	s197,
	s198,
	s199,
	s200,
	s201,
	s202,
	s203,
	s204,
	s205,
	s206,
	s207,
	s208,
	s209,
	s210,
	s211,
	s212,
	s213,
	s214,
	s215,
	s216,
	s217,
	s218,
	s219,
	s220,
	s221,
	s222,
	s223,
	s224,
	s225,
	s226,
	s227,
	s228,
	s229,
	s230,
	s231,
	s232,
	s233,
	s234,
	s235,
	s236,
	s237,
	s238,
	s239,
	s240,
	s241,
	s242,
	s243,
	s244,
	s245,
	s246,
	s247,
	s248,
	s249,
	s250,
	s251,
	s252,
	s253,
	s254,
	s255,
	s256,
	s257,
	s258,
	s259,
	s260,
	s261,
	s262,
	s263,
	s264,
	s265,
	s266,
	s267,
	s268,
	s269,
	s270,
	s271,
	s272,
	s273,
	s274,
	s275,
	s276,
	s277,
	s278,
	s279,
	s280,
	s281,
	s282,
	s283,
	s284,
	s285,
	s286,
	s287,
	s288,
	s289,
	s290,
	s291,
	s292,
	s293,
	s294,
	s295,
	s296,
	s297,
	s298,
	s299,
	s300,
	s301,
	s302,
	s303,
	s304,
	s305,
	s306,
	s307,
	s308,
	s309,
	s310,
	s311,
	s312,
	s313,
	s314,
	s315,
	s316,
	s317,
	s318,
	s319,
	s320,
	s321,
	s322,
	s323,
	s324,
	s325,
	s326,
	s327,
	s328,
	s329,
	s330,
	s331,
	s332,
	s333,
	s334,
	s335,
	s336,
	s337,
	s338,
	s339,
	s340,
	s341,
	s342,
	s343,
	s344,
	s345,
	s346,
	s347,
	s348,
	s349,
	s350,
	s351,
	s352,
	s353,
	s354,
	s355,
	s356,
	s357,
	s358,
	s359,
	s360,
	s361,
	s362,
	s363,
	s364,
	s365,
	s366,
	s367,
	s368,
	s369,
	s370,
	s371,
	s372,
	s373,
	s374,
	s375,
	s376,
	s377,
	s378,
	s379,
	s380,
	s381,
	s382,
	s383,
	s384,
	s385,
	s386,
	s387,
	s388,
	s389,
	s390,
	s391,
	s392,
	s393,
	s394,
	s395,
	s396,
	s397,
	s398,
	s399,
	s400,
	s401,
	s402,
	s403,
	s404,
	s405,
	s406,
	s407,
	s408,
	s409,
	s410,
	s411,
	s412,
	s413,
	s414,
	s415,
	s416,
	s417,
	s418,
	s419,
	s420,
	s421,
	s422,
	s423,
	s424,
	s425,
	s426,
	s427,
	s428,
	s429,
	s430,
	s431,
	s432,
	s433,
	s434,
	s435,
	s436,
	s437,
	s438,
	s439,
	s440,
	s441,
	s442,
	s443,
	s444,
	s445,
	s446,
	s447,
	s448,
	s449,
	s450,
	s451,
	s452,
	s453,
	s454,
	s455,
	s456,
	s457,
	s458,
	s459,
	s460,
	s461,
	s462,
	s463,
	s464,
	s465,
	s466,
	s467,
	s468,
	s469,
	s470,
	s471,
	s472,
	s473,
	s474,
	s475,
	s476,
	s477,
	s478,
	s479,
	s480,
	s481,
	s482,
	s483,
	s484,
	s485,
	s486,
	s487,
	s488,
	s489,
	s490,
	s491,
	s492,
	s493,
	s494,
	s495,
	s496,
	s497,
	s498,
	s499,
	s500,
	s501,
	s502,
	s503,
	s504,
	s505,
	s506,
	s507,
	s508,
	s509,
	s510,
	s511,
	s512,
	s513,
	s514,
	s515,
	s516,
	s517,
	s518,
	s519,
	s520,
	s521,
	s522,
	s523,
	s524,
	s525,
	s526,
	s527,
	s528,
	s529,
	s530,
	s531,
	s532,
	s533,
	s534,
	s535,
	s536,
	s537,
	s538,
	s539,
	s540,
	s541,
	s542,
	s543,
	s544,
	s545,
	s546,
	s547,
	s548,
	s549,
	s550,
	s551,
	s552,
	s553,
	s554,
	s555,
	s556,
	s557,
	s558,
	s559,
	s560,
	s561,
	s562,
	s563,
	s564,
	s565,
	s566,
	s567,
	s568,
	s569,
	s570,
	s571,
	s572,
	s573,
	s574,
	s575,
	s576,
	s577,
	s578,
	s579,
	s580,
	s581,
	s582,
	s583,
	s584,
	s585,
	s586,
	s587,
	s588,
	s589,
	s590,
	s591,
	s592,
	s593,
	s594,
	s595,
	s596,
	s597,
	s598,
	s599,
	s600,
	s601,
	s602,
	s603,
	s604,
	s605,
	s606,
	s607,
	s608,
	s609,
	s610,
	s611,
	s612,
	s613,
	s614,
	s615,
	s616,
	s617,
	s618,
	s619,
	s620,
	s621,
	s622,
	s623,
	s624,
	s625,
	s626,
	s627,
	s628,
	s629,
	s630,
	s631,
	s632,
	s633,
	s634,
	s635,
	s636,
	s637,
	s638,
	s639,
	s640,
	s641,
	s642,
	s643,
	s644,
	s645,
	s646,
	s647,
	s648,
	s649,
	s650,
	s651,
	s652,
	s653,
	s654,
	s655,
	s656,
	s657,
	s658,
	s659,
	s660,
	s661,
	s662,
	s663,
	s664,
	s665,
	s666,
	s667,
	s668,
	s669,
	s670,
	s671,
	s672,
	s673,
	s674,
	s675,
	s676,
	s677,
	s678,
	s679,
	s680,
	s681,
	s682,
	s683,
	s684,
	s685,
	s686,
	s687,
	s688,
	s689,
	s690,
	s691,
	s692,
	s693,
	s694,
	s695,
	s696,
	s697,
	s698,
	s699,
	s700,
	s701,
	s702,
	s703,
	s704,
	s705,
	s706,
	s707,
	s708,
	s709,
	s710,
	s711,
	s712,
	s713,
	s714,
	s715,
	s716,
	s717,
	s718,
	s719,
	s720,
	s721,
	s722,
	s723,
	s724,
	s725,
	s726,
	s727,
	s728,
	s729,
	s730,
	s731,
	s732,
	s733,
	s734,
	s735,
	s736,
	s737,
	s738,
	s739,
	s740,
	s741,
	s742,
	s743,
	s744,
	s745,
	s746,
	s747,
	s748,
	s749,
	s750,
	s751,
	s752,
	s753,
	s754,
	s755,
	s756,
	s757,
	s758,
	s759,
	s760,
	s761,
	s762,
	s763,
	s764,
	s765,
	s766,
	s767,
	s768,
	s769,
	s770,
	s771,
	s772,
	s773,
	s774,
	s775,
	s776,
	s777,
	s778,
	s779,
	s780,
	s781,
	s782,
	s783,
	s784,
	s785,
	s786,
	s787,
	s788,
	s789,
	s790,
	s791,
	s792,
	s793,
	s794,
	s795,
	s796,
	s797,
	s798,
	s799,
	s800,
	s801,
	s802,
	s803,
	s804,
	s805,
	s806,
	s807,
	s808,
	s809,
	s810,
	s811,
	s812,
	s813,
	s814,
	s815,
	s816,
	s817,
	s818,
	s819,
	s820,
	s821,
	s822,
	s823,
	s824,
	s825,
	s826,
	s827,
	s828,
	s829,
	s830,
	s831,
	s832,
	s833,
	s834,
	s835,
	s836,
	s837,
	s838,
	s839,
	s840,
	s841,
	s842,
	s843,
	s844,
	s845,
	s846,
	s847,
	s848,
	s849,
	s850,
	s851,
	s852,
	s853,
	s854,
	s855,
	s856,
	s857,
	s858,
	s859,
	s860,
	s861,
	s862,
	s863,
	s864,
	s865,
	s866,
	s867,
	s868,
	s869,
	s870,
	s871,
	s872,
	s873,
	s874,
	s875,
	s876,
	s877,
	s878,
	s879,
	s880,
	s881,
	s882,
	s883,
	s884,
	s885,
	s886,
	s887,
	s888,
	s889,
	s890,
	s891,
	s892,
	s893,
	s894,
	s895,
	s896,
	s897,
	s898,
	s899,
	s900,
	s901,
	s902,
	s903,
	s904,
	s905,
	s906,
	s907,
	s908,
	s909,
	s910,
	s911,
	s912,
	s913,
	s914,
	s915,
	s916,
	s917,
	s918,
	s919,
	s920,
	s921,
	s922,
	s923,
	s924,
	s925,
	s926,
	s927,
	s928,
	s929,
	s930,
	s931,
	s932,
	s933,
	s934,
	s935,
	s936,
	s937,
	s938,
	s939,
	s940,
	s941,
	s942,
	s943,
	s944,
	s945,
	s946,
	s947,
	s948,
	s949,
	s950,
	s951,
	s952,
	s953,
	s954,
	s955,
	s956,
	s957,
	s958,
	s959,
	s960,
	s961,
	s962,
	s963,
	s964,
	s965,
	s966,
	s967,
	s968,
	s969,
	s970,
	s971,
	s972,
	s973,
	s974,
	s975,
	s976,
	s977,
	s978,
	s979,
	s980,
	s981,
	s982,
	s983,
	s984,
	s985,
	s986,
	s987,
	s988,
	s989,
	s990,
	s991,
	s992,
	s993,
	s994,
	s995,
	s996,
	s997,
	s998,
	s999,
	s1000,
	s1001,
	s1002,
	s1003,
	s1004,
	s1005,
	s1006,
	s1007,
	s1008,
	s1009,
	s1010,
	s1011,
	s1012,
	s1013,
	s1014,
	s1015,
	s1016,
	s1017,
	s1018,
	s1019,
	s1020,
	s1021,
	s1022,
	s1023,
	s1024,
	s1025,
	s1026,
	s1027,
	s1028,
	s1029,
	s1030,
	s1031,
	s1032,
	s1033,
	s1034,
	s1035,
	s1036,
	s1037,
	s1038,
	s1039,
	s1040,
	s1041,
	s1042,
	s1043,
	s1044,
	s1045,
	s1046,
	s1047,
	s1048,
	s1049,
	s1050,
	s1051,
	s1052,
	s1053,
	s1054,
	s1055,
	s1056,
	s1057,
	s1058,
	s1059,
	s1060,
	s1061,
	s1062,
	s1063,
	s1064,
	s1065,
	s1066,
	s1067,
	s1068,
	s1069,
	s1070,
	s1071,
	s1072,
	s1073,
	s1074,
	s1075,
	s1076,
	s1077,
	s1078,
	s1079,
	s1080,
	s1081,
	s1082,
	s1083,
	s1084,
	s1085,
	s1086,
	s1087,
	s1088,
	s1089,
	s1090,
	s1091,
	s1092,
	s1093,
	s1094,
	s1095,
	s1096,
	s1097,
	s1098,
	s1099,
	s1100,
	s1101,
	s1102,
	s1103,
	s1104,
	s1105,
	s1106,
	s1107,
	s1108,
	s1109,
	s1110,
	s1111,
	s1112,
	s1113,
	s1114,
	s1115,
	s1116,
	s1117,
	s1118,
	s1119,
	s1120,
	s1121,
	s1122,
	s1123,
	s1124,
	s1125,
	s1126,
	s1127,
	s1128,
	s1129,
	s1130,
	s1131,
	s1132,
	s1133,
	s1134,
	s1135,
	s1136,
	s1137,
	s1138,
	s1139,
	s1140,
	s1141,
	s1142,
	s1143,
	s1144,
	s1145,
	s1146,
	s1147,
	s1148,
	s1149,
	s1150,
	s1151,
	s1152,
	s1153,
	s1154,
	s1155,
	s1156,
	s1157,
	s1158,
	s1159,
	s1160,
	s1161,
	s1162,
	s1163,
	s1164,
	s1165,
	s1166,
	s1167,
	s1168,
	s1169,
	s1170,
	s1171,
	s1172,
	s1173,
	s1174,
	s1175,
	s1176,
	s1177,
	s1178,
	s1179,
	s1180,
	s1181,
	s1182,
	s1183,
	s1184,
	s1185,
	s1186,
	s1187,
	s1188,
	s1189,
	s1190,
	s1191,
	s1192,
	s1193,
	s1194,
	s1195,
	s1196,
	s1197,
	s1198,
	s1199,
	s1200,
	s1201,
	s1202,
	s1203,
	s1204,
	s1205,
	s1206,
	s1207,
	s1208,
	s1209,
	s1210,
	s1211,
	s1212,
	s1213,
	s1214,
	s1215,
	s1216,
	s1217,
	s1218,
	s1219,
	s1220,
	s1221,
	s1222,
	s1223,
	s1224,
	s1225,
	s1226,
	s1227,
	s1228,
	s1229,
	s1230,
	s1231,
	s1232,
	s1233,
	s1234,
	s1235,
	s1236,
	s1237,
	s1238,
	s1239,
	s1240,
	s1241,
	s1242,
	s1243,
	s1244,
	s1245,
	s1246,
	s1247,
	s1248,
	s1249,
	s1250,
	s1251,
	s1252,
	s1253,
	s1254,
	s1255,
	s1256,
	s1257,
	s1258,
	s1259,
	s1260,
	s1261,
	s1262,
	s1263,
	s1264,
	s1265,
	s1266,
	s1267,
	s1268,
	s1269,
	s1270,
	s1271,
	s1272,
	s1273,
	s1274,
	s1275,
	s1276,
	s1277,
	s1278,
	s1279,
	s1280,
	s1281,
	s1282,
	s1283,
	s1284,
	s1285,
	s1286,
	s1287,
	s1288,
	s1289,
	s1290,
	s1291,
	s1292,
	s1293,
	s1294,
	s1295,
	s1296,
	s1297,
	s1298,
	s1299,
	s1300,
	s1301,
	s1302,
	s1303,
	s1304,
	s1305,
	s1306,
	s1307,
	s1308,
	s1309,
	s1310,
	s1311,
	s1312,
	s1313,
	s1314,
	s1315,
	s1316,
	s1317,
	s1318,
	s1319,
	s1320,
	s1321,
	s1322,
	s1323,
	s1324,
	s1325,
	s1326,
	s1327,
	s1328,
	s1329,
	s1330,
	s1331,
	s1332,
	s1333,
	s1334,
	s1335,
	s1336,
	s1337,
	s1338,
	s1339,
	s1340,
	s1341,
	s1342,
	s1343,
	s1344,
	s1345,
	s1346,
	s1347,
	s1348,
	s1349,
	s1350,
	s1351,
	s1352,
	s1353,
	s1354,
	s1355,
	s1356,
	s1357,
	s1358,
	s1359,
	s1360,
	s1361,
	s1362,
	s1363,
	s1364,
	s1365,
	s1366,
	s1367,
	s1368,
	s1369,
	s1370,
	s1371,
	s1372,
	s1373,
	s1374,
	s1375,
	s1376,
	s1377,
	s1378,
	s1379,
	s1380,
	s1381,
	s1382,
	s1383,
	s1384,
	s1385,
	s1386,
	s1387,
	s1388,
	s1389,
	s1390,
	s1391,
	s1392,
	s1393,
	s1394,
	s1395,
	s1396,
	s1397,
	s1398,
	s1399,
	s1400,
	s1401,
	s1402,
	s1403,
	s1404,
	s1405,
	s1406,
	s1407,
	s1408,
	s1409,
	s1410,
	s1411,
	s1412,
	s1413,
	s1414,
	s1415,
	s1416,
	s1417,
	s1418,
	s1419,
	s1420,
	s1421,
	s1422,
	s1423,
	s1424,
	s1425,
	s1426,
	s1427,
	s1428,
	s1429,
	s1430,
	s1431,
	s1432,
	s1433,
	s1434,
	s1435,
	s1436,
	s1437,
	s1438,
	s1439,
	s1440,
	s1441,
	s1442,
	s1443,
	s1444,
	s1445,
	s1446,
	s1447,
	s1448,
	s1449,
	s1450,
	s1451,
	s1452,
	s1453,
	s1454,
	s1455,
	s1456,
	s1457,
	s1458,
	s1459,
	s1460,
	s1461,
	s1462,
	s1463,
	s1464,
	s1465,
	s1466,
	s1467,
	s1468,
	s1469,
	s1470,
	s1471,
	s1472,
	s1473,
	s1474,
	s1475,
	s1476,
	s1477,
	s1478,
	s1479,
	s1480,
	s1481,
	s1482,
	s1483,
	s1484,
	s1485,
	s1486,
	s1487,
	s1488,
	s1489,
	s1490,
	s1491,
	s1492,
	s1493,
	s1494,
	s1495,
	s1496,
	s1497,
	s1498,
	s1499,
	s1500,
	s1501,
	s1502,
	s1503,
	s1504,
	s1505,
	s1506,
	s1507,
	s1508,
	s1509,
	s1510,
	s1511,
	s1512,
	s1513,
	s1514,
	s1515,
	s1516,
	s1517,
	s1518,
	s1519,
	s1520,
	s1521,
	s1522,
	s1523,
	s1524,
	s1525,
	s1526,
	s1527,
	s1528,
	s1529,
	s1530,
	s1531,
	s1532,
	s1533,
	s1534,
	s1535,
	s1536,
	s1537,
	s1538,
	s1539,
	s1540,
	s1541,
	s1542,
	s1543,
	s1544,
	s1545,
	s1546,
	s1547,
	s1548,
	s1549,
	s1550,
	s1551,
	s1552,
	s1553,
	s1554,
	s1555,
	s1556,
	s1557,
	s1558,
	s1559,
	s1560,
	s1561,
	s1562,
	s1563,
	s1564,
	s1565,
	s1566,
	s1567,
	s1568,
	s1569,
	s1570,
	s1571,
	s1572,
	s1573,
	s1574,
	s1575,
	s1576,
	s1577,
	s1578,
	s1579,
	s1580,
	s1581,
	s1582,
	s1583,
	s1584,
	s1585,
	s1586,
	s1587,
	s1588,
	s1589,
	s1590,
	s1591,
	s1592,
	s1593,
	s1594,
	s1595,
	s1596,
	s1597,
	s1598,
	s1599,
	s1600,
	s1601,
	s1602,
	s1603,
	s1604,
	s1605,
	s1606,
	s1607,
	s1608,
	s1609,
	s1610,
	s1611,
	s1612,
	s1613,
	s1614,
	s1615,
	s1616,
	s1617,
	s1618,
	s1619,
	s1620,
	s1621,
	s1622,
	s1623,
	s1624,
	s1625,
	s1626,
	s1627,
	s1628,
	s1629,
	s1630,
	s1631,
	s1632,
	s1633,
	s1634,
	s1635,
	s1636,
	s1637,
	s1638,
	s1639,
	s1640,
	s1641,
	s1642,
	s1643,
	s1644,
	s1645,
	s1646,
	s1647,
	s1648,
	s1649,
	s1650,
	s1651,
	s1652,
	s1653,
	s1654,
	s1655,
	s1656,
	s1657,
	s1658,
	s1659,
	s1660,
	s1661,
	s1662,
	s1663,
	s1664,
	s1665,
	s1666,
	s1667,
	s1668,
	s1669,
	s1670,
	s1671,
	s1672,
	s1673,
	s1674,
	s1675,
	s1676,
	s1677,
	s1678,
	s1679,
	s1680,
	s1681,
	s1682,
	s1683,
	s1684,
	s1685,
	s1686,
	s1687,
	s1688,
	s1689,
	s1690,
	s1691,
	s1692,
	s1693,
	s1694,
	s1695,
	s1696,
	s1697,
	s1698,
	s1699,
	s1700,
	s1701,
	s1702,
	s1703,
	s1704,
	s1705,
	s1706,
	s1707,
	s1708,
	s1709,
	s1710,
	s1711,
	s1712,
	s1713,
	s1714,
	s1715,
	s1716,
	s1717,
	s1718,
	s1719,
	s1720,
	s1721,
	s1722,
	s1723,
	s1724,
	s1725,
	s1726,
	s1727,
	s1728,
	s1729,
	s1730,
	s1731,
	s1732,
	s1733,
	s1734,
	s1735,
	s1736,
	s1737,
	s1738,
	s1739,
	s1740,
	s1741,
	s1742,
	s1743,
	s1744,
	s1745,
	s1746,
	s1747,
	s1748,
	s1749,
	s1750,
	s1751,
	s1752,
	s1753,
	s1754,
	s1755,
	s1756,
	s1757,
	s1758,
	s1759,
	s1760,
	s1761,
	s1762,
	s1763,
	s1764,
	s1765,
	s1766,
	s1767,
	s1768,
	s1769,
	s1770,
	s1771,
	s1772,
	s1773,
	s1774,
	s1775,
	s1776,
	s1777,
	s1778,
	s1779,
	s1780,
	s1781,
	s1782,
	s1783,
	s1784,
	s1785,
	s1786,
	s1787,
	s1788,
	s1789,
	s1790,
	s1791,
	s1792,
	s1793,
	s1794,
	s1795,
	s1796,
	s1797,
	s1798,
	s1799,
	s1800,
	s1801,
	s1802,
	s1803,
	s1804,
	s1805,
	s1806,
	s1807,
	s1808,
	s1809,
	s1810,
	s1811,
	s1812,
	s1813,
	s1814,
	s1815,
	s1816,
	s1817,
	s1818,
	s1819,
	s1820,
	s1821,
	s1822,
	s1823,
	s1824,
	s1825,
	s1826,
	s1827,
	s1828,
	s1829,
	s1830,
	s1831,
	s1832,
	s1833,
	s1834,
	s1835,
	s1836,
	s1837,
	s1838,
	s1839,
	s1840,
	s1841,
	s1842,
	s1843,
	s1844,
	s1845,
	s1846,
	s1847,
	s1848,
	s1849,
	s1850,
	s1851,
	s1852,
	s1853,
	s1854,
	s1855,
	s1856,
	s1857,
	s1858,
	s1859,
	s1860,
	s1861,
	s1862,
	s1863,
	s1864,
	s1865,
	s1866,
	s1867,
	s1868,
	s1869,
	s1870,
	s1871,
	s1872,
	s1873,
	s1874,
	s1875,
	s1876,
	s1877,
	s1878,
	s1879,
	s1880,
	s1881,
	s1882,
	s1883,
	s1884,
	s1885,
	s1886,
	s1887,
	s1888,
	s1889,
	s1890,
	s1891,
	s1892,
	s1893,
	s1894,
	s1895,
	s1896,
	s1897,
	s1898,
	s1899,
	s1900,
	s1901,
	s1902,
	s1903,
	s1904,
	s1905,
	s1906,
	s1907,
	s1908,
	s1909,
	s1910,
	s1911,
	s1912,
	s1913,
	s1914,
	s1915,
	s1916,
	s1917,
	s1918,
	s1919,
	s1920,
	s1921,
	s1922,
	s1923,
	s1924,
	s1925,
	s1926,
	s1927,
	s1928,
	s1929,
	s1930,
	s1931,
	s1932,
	s1933,
	s1934,
	s1935,
	s1936,
	s1937,
	s1938,
	s1939,
	s1940,
	s1941,
	s1942,
	s1943,
	s1944,
	s1945,
	s1946,
	s1947,
	s1948,
	s1949,
	s1950,
	s1951,
	s1952,
	s1953,
	s1954,
	s1955,
	s1956,
	s1957,
	s1958,
	s1959,
	s1960,
	s1961,
	s1962,
	s1963,
	s1964,
	s1965,
	s1966,
	s1967,
	s1968,
	s1969,
	s1970,
	s1971,
	s1972,
	s1973,
	s1974,
	s1975,
	s1976,
	s1977,
	s1978,
	s1979,
	s1980,
	s1981,
	s1982,
	s1983,
	s1984,
	s1985,
	s1986,
	s1987,
	s1988,
	s1989,
	s1990,
	s1991,
	s1992,
	s1993,
	s1994,
	s1995,
	s1996,
	s1997,
	s1998,
	s1999,
	s2000,
	s2001,
	s2002,
	s2003,
	s2004,
	s2005,
	s2006,
	s2007,
	s2008,
	s2009,
	s2010,
	s2011,
	s2012,
	s2013,
	s2014,
	s2015,
	s2016,
	s2017,
	s2018,
	s2019,
	s2020,
	s2021,
	s2022,
	s2023,
	s2024,
	s2025,
	s2026,
	s2027,
	s2028,
	s2029,
	s2030,
	s2031,
	s2032,
	s2033,
	s2034,
	s2035,
	s2036,
	s2037,
	s2038,
	s2039,
	s2040,
	s2041,
	s2042,
	s2043,
	s2044,
	s2045,
	s2046,
	s2047,
	s2048,
	s2049,
	s2050,
	s2051,
	s2052,
	s2053,
	s2054,
	s2055,
	s2056,
	s2057,
	s2058,
	s2059,
	s2060,
	s2061,
	s2062,
	s2063,
	s2064,
	s2065,
	s2066,
	s2067,
	s2068,
	s2069,
	s2070,
	s2071,
	s2072,
	s2073,
	s2074,
	s2075,
	s2076,
	s2077,
	s2078,
	s2079,
	s2080,
	s2081,
	s2082,
	s2083,
	s2084,
	s2085,
	s2086,
	s2087,
	s2088,
	s2089,
	s2090,
	s2091,
	s2092,
	s2093,
	s2094,
	s2095,
	s2096,
	s2097,
	s2098,
	s2099,
	s2100,
	s2101,
	s2102,
	s2103,
	s2104,
	s2105,
	s2106,
	s2107,
	s2108,
	s2109,
	s2110,
	s2111,
	r0 = 4242,
	r1,
	r2,
	r3,
	r4,
	r5,
	r6,
	r7,
	r8,
	r9,
	r10,
	r11,
	r12,
	r13,
	r14,
	r15,
	r16,
	r17,
	r18,
	r19,
	r20,
	r21,
	r22,
	r23,
	r24,
	r25,
	r26,
	r27,
	r28,
	r29,
	r30,
	r31,
	r32,
	r33,
	r34,
	r35,
	r36,
	r37,
	r38,
	r39,
	r40,
	r41,
	r42,
	r43,
	r44,
	r45,
	r46,
	r47,
	r48,
	r49,
	r50,
	r51,
	r52,
	r53,
	r54,
	r55,
	r56,
	r57,
	r58,
	r59,
	r60,
	r61,
	r62,
	r63,
	r64,
	r65,
	r66,
	r67,
	r68,
	r69,
	r70,
	r71,
	r72,
	r73,
	r74,
	r75,
	r76,
	r77,
	r78,
	r79,
	r80,
	r81,
	r82,
	r83,
	r84,
	r85,
	r86,
	r87,
	r88,
	r89,
	r90,
	r91,
	r92,
	r93,
	r94,
	r95,
	r96,
	r97,
	r98,
	r99,
	r100,
	r101,
	r102,
	r103,
	r104,
	r105,
	r106,
	r107,
	r108,
	r109,
	r110,
	r111,
	r112,
	r113,
	r114,
	r115,
	r116,
	r117,
	r118,
	r119,
	r120,
	r121,
	r122,
	r123,
	r124,
	r125,
	r126,
	r127,
	r128,
	r129,
	r130,
	r131,
	r132,
	r133,
	r134,
	r135,
	r136,
	r137,
	r138,
	r139,
	r140,
	r141,
	r142,
	r143,
	r144,
	r145,
	r146,
	r147,
	r148,
	r149,
	r150,
	r151,
	r152,
	r153,
	r154,
	r155,
	r156,
	r157,
	r158,
	r159,
	r160,
	r161,
	r162,
	r163,
	r164,
	r165,
	r166,
	r167,
	r168,
	r169,
	r170,
	r171,
	r172,
	r173,
	r174,
	r175,
	r176,
	r177,
	r178,
	r179,
	r180,
	r181,
	r182,
};

enum e_symbol {
	PROGRAM = 1,
	COMPLETE_COMMANDS,
	COMPLETE_COMMAND,
	LIST,
	AND_OR,
	PIPELINE,
	PIPE_SEQUENCE,
	COMMAND,
	COMPOUND_COMMAND,
	SUBSHELL,
	COMPOUND_LIST,
	TERM,
	FOR_CLAUSE,
	NAME,
	SYM_IN,
	WORDLIST,
	CASE_CLAUSE,
	CASE_LIST_NS,
	CASE_LIST,
	CASE_ITEM_NS,
	CASE_ITEM,
	PATTERN,
	IF_CLAUSE,
	ELSE_PART,
	WHILE_CLAUSE,
	UNTIL_CLAUSE,
	FUNCTION_DEFINITION,
	FUNCTION_BODY,
	FNAME,
	BRACE_GROUP,
	DO_GROUP,
	SIMPLE_COMMAND,
	CMD_PREFIX,
	CMD_SUFFIX,
	CMD_NAME,
	CMD_WORD,
	REDIRECT_LIST,
	IO_REDIRECT,
	IO_FILE,
	FILENAME,
	IO_HERE,
	HERE_END,
	NEWLINE_LIST,
	LINEBREAK,
	SEPARATOR_OP,
	SEPARATOR,
	SEQUENTIAL_SEP,
};

#endif
