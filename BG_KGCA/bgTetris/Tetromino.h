// 텍스트 밝은색
#define TEXT_COLOR_WL (0x07 | 0x08)
#define TEXT_COLOR_KL (0x00 | 0x08)
#define TEXT_COLOR_RL (0x04 | 0x08)
#define TEXT_COLOR_GL (0x02 | 0x08)
#define TEXT_COLOR_BL (0x01 | 0x08)
#define TEXT_COLOR_CL (0x03 | 0x08)
#define TEXT_COLOR_ML (0x05 | 0x08)
#define TEXT_COLOR_YL (0x06 | 0x08)
// 텍스트 어두운색
#define TEXT_COLOR_WD (0x07)
#define TEXT_COLOR_KD (0x00)
#define TEXT_COLOR_RD (0x04)
#define TEXT_COLOR_GD (0x02)
#define TEXT_COLOR_BD (0x01)
#define TEXT_COLOR_CD (0x03)
#define TEXT_COLOR_MD (0x05)
#define TEXT_COLOR_YD (0x06)
// 배경 밝은색
#define BACK_COLOR_WL (0x70 | 0x80)
#define BACK_COLOR_KL (0x00 | 0x80)
#define BACK_COLOR_RL (0x40 | 0x80)
#define BACK_COLOR_GL (0x20 | 0x80)
#define BACK_COLOR_BL (0x10 | 0x80)
#define BACK_COLOR_CL (0x30 | 0x80)
#define BACK_COLOR_ML (0x50 | 0x80)
#define BACK_COLOR_YL (0x60 | 0x80)
// 배경 어두운색
#define BACK_COLOR_WD (0x70)
#define BACK_COLOR_KD (0x00)
#define BACK_COLOR_RD (0x40)
#define BACK_COLOR_GD (0x20)
#define BACK_COLOR_BD (0x10)
#define BACK_COLOR_CD (0x30)
#define BACK_COLOR_MD (0x50)
#define BACK_COLOR_YD (0x60)


const char BoxChar[9][3] = {
	//"  ",
	//"  ", // ──
	//"  ", //  □
	//"  ", // ＿|＿
	//"  ", // ＿＿|
	//"  ", //  |＿＿
	//"  ", // ＿|￣
	//"  ", // ￣|＿
	//"  "  // 벽
	"  ",
	"■", // ──
	"■", //  □
	"■", // ＿|＿
	"■", // ＿＿|
	"■", //  |＿＿
	"■", // ＿|￣
	"■", // ￣|＿
	"■"  // 벽
};

const int BlockColor[9] = {
	TEXT_COLOR_KD | BACK_COLOR_KD,
	TEXT_COLOR_CL | BACK_COLOR_CD,
	TEXT_COLOR_YL | BACK_COLOR_YD,
	TEXT_COLOR_ML | BACK_COLOR_MD,
	TEXT_COLOR_WL | BACK_COLOR_WD,
	TEXT_COLOR_BL | BACK_COLOR_BD,
	TEXT_COLOR_GL | BACK_COLOR_GD,
	TEXT_COLOR_RL | BACK_COLOR_RD,
	TEXT_COLOR_KL | BACK_COLOR_KL
};

const int Tetromino[7][4][4][4] =
{
	{
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 }
		}
	},
	{
		{
			{ 0, 2, 2, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 2, 2, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 2, 2, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 2, 2, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{
			{ 0, 3, 0, 0 },
			{ 3, 3, 3, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 3, 0, 0 },
			{ 3, 3, 0, 0 },
			{ 0, 3, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 3, 3, 3, 0 },
			{ 0, 3, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 3, 0, 0 },
			{ 0, 3, 3, 0 },
			{ 0, 3, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{
			{ 0, 0, 4, 0 },
			{ 4, 4, 4, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 4, 4, 0, 0 },
			{ 0, 4, 0, 0 },
			{ 0, 4, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 4, 4, 4, 0 },
			{ 4, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 4, 0, 0 },
			{ 0, 4, 0, 0 },
			{ 0, 4, 4, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{
			{ 0, 5, 0, 0 },
			{ 0, 5, 5, 5 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 5, 0 },
			{ 0, 0, 5, 0 },
			{ 0, 5, 5, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 5, 5, 5 },
			{ 0, 0, 0, 5 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 5, 5 },
			{ 0, 0, 5, 0 },
			{ 0, 0, 5, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{
			{ 0, 6, 6, 0 },
			{ 6, 6, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 6, 0, 0 },
			{ 0, 6, 6, 0 },
			{ 0, 0, 6, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 6, 6, 0 },
			{ 6, 6, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 6, 0, 0 },
			{ 0, 6, 6, 0 },
			{ 0, 0, 6, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{
			{ 0, 7, 7, 0 },
			{ 0, 0, 7, 7 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 7, 0 },
			{ 0, 7, 7, 0 },
			{ 0, 7, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 7, 7, 0 },
			{ 0, 0, 7, 7 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 7, 0 },
			{ 0, 7, 7, 0 },
			{ 0, 7, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	}
};
