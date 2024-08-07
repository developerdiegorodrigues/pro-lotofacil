#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include <shlwapi.h>

//-------------------------------------------------->>
extern HWND hwndMain, hwndSec, hwndPanelA, hwndPanelB, hwndPanelC, hwndPanelD, hwndPaleta;
extern HWND hExtA, hExtB, hExtC, hExtD, hExtE, hExtF, hExtG;
extern HWND hListView_Pc, hListView_ext_a, hListView_ext_c, hListView_ext_e;
extern HINSTANCE hInstance;
extern HBRUSH hBrushButton;
extern HBITMAP hPrimary, hSecond, hTertiary, hQuaternay;
extern INT intMainTimerId;
extern BOOL bWindowStatus;
extern LONG longCardExtA[7][18];
extern LONG longMaxExtC;
extern LONG longMaxExtE;
extern INT longNumExtG[16];
//-------------------------------------------------->>
extern void error(LPSTR, INT);
extern void show_message(LPSTR, INT);
extern void to_size(INT, INT, INT, WPARAM);
extern void general_block(INT);
extern void general_wm_paint(HWND, HDC);
extern int general_available_disk(HWND, LONG);

extern void wm_size(VOID);
extern void wm_paint(VOID);
extern void wm_create(HWND);
extern void wm_timer(WPARAM);
extern void wm_notify(INT, LPNMHDR);
extern void wm_command(HWND, WPARAM, LPARAM);

extern void panel_c_gerate_total(INT, HWND);
extern void panel_c_run(INT, HWND);
extern void panel_c_resume(INT, HWND);
extern void panel_c_check(INT, HWND);

extern void ext_a_change(INT, INT);
extern void ext_a_list_view_insert_data(HWND);

extern void ext_c_change(INT, INT);
extern void ext_c_list_view_insert_data(HWND);

extern void ext_e_change(INT, INT);
extern void ext_e_list_view_insert_data(HWND);

extern void ext_g_fill(HWND);
extern void ext_g_analyze(HWND);
extern int ext_g_save_image(LONG[], LONG);
extern void ext_g_save_card(INT, HWND);

extern LRESULT CALLBACK MinProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK MaxProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK CloseProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK SecProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PltProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelAProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelBProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelCProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelDProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelDExtProcA(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelDExtProcB(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelDExtProcC(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelDExtProcD(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelDExtProcE(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelDExtProcF(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK PanelDExtProcG(HWND, UINT, WPARAM, LPARAM);
//-------------------------------------------------->>
// Geral
#define AUTHOR					"@devdiegorodrigues"
#define PROJECT_TITLE			"ProLotofacil"
#define MAIN_CLASS_NAME			"MainWindowClass"
#define MAX_CLASS_NAME			"MaxWindowClass"
#define MIN_CLASS_NAME			"MinWindowClass"
#define CLOSE_CLASS_NAME		"CloseWindowClass"
#define SEC_CLASS_NAME			"SecWindowClass"
#define PLT_CLASS_NAME			"PltWindowClass"

#define PAINEL_A_CLASS_NAME		"PanelAWindowClass"
#define PAINEL_B_CLASS_NAME		"PanelBWindowClass"
#define PAINEL_C_CLASS_NAME		"PanelCWindowClass"
#define PAINEL_D_CLASS_NAME		"PanelDWindowClass"

#define PD_EXT_A_CLASS_NAME		"PDExtAWindowClass"
#define PD_EXT_B_CLASS_NAME		"PDExtBWindowClass"
#define PD_EXT_C_CLASS_NAME		"PDExtCWindowClass"
#define PD_EXT_D_CLASS_NAME		"PDExtDWindowClass"
#define PD_EXT_E_CLASS_NAME		"PDExtEWindowClass"
#define PD_EXT_F_CLASS_NAME		"PDExtFWindowClass"
#define PD_EXT_G_CLASS_NAME		"PDExtGWindowClass"

#define MAIN_WINDOW_WIDTH			800 // inicial
#define MAIN_WINDOW_HEIGHT			600 // inicial
#define MAIN_WINDOW_MINIMUM_WIDTH	790 // mínimo
#define MAIN_WINDOW_MAXIMUM_WIDTH	590 // mínimo
#define TITLE_BAR_HEIGHT			45
#define EDGE_WIDTH					7
#define RESIZE_BORDER				10 // borda para redimensionar a janela
#define DATA_LOTTERY_GAME			"data_base"
#define DATA_LOTTERY_TOTAL			"total_data_base"
#define DATA_RESULT					"res_data_base"
#define MESSAGE_A					1000
#define MESSAGE_B					1001
#define MESSAGE_BLOCK				1002
#define MESSAGE_UNBLOCK				1003
#define START						1010
#define EXECUTE						1011
#define FINALIZE					1012

// Cores
#define COLOR_MAIN_TITLE			RGB(235, 235, 235) // RGB(155, 186, 0)
#define COLOR_MAIN_BACKGROUND		RGB(217, 230, 247)
#define COLOR_MAIN_TITLE_BAR		RGB(51, 51, 51)
#define COLOR_MAIN_BORDER			RGB(51, 51, 51)
#define COLOR_SECARY				RGB(82, 82, 82)
#define COLOR_MIN_ACTIVE			RGB(0, 158, 235)
#define COLOR_MAX_ACTIVE			RGB(119, 180, 0)
#define COLOR_CLOSE_ACTIVE			RGB(238, 69, 26)
#define COLOR_PANEL_BACKGROUND		RGB(255, 255, 255)
#define COLOR_TEXT_LV01				RGB(0, 115, 198)
#define COLOR_CARD_BACKGROUND		RGB(255, 255, 235) // RGB(255, 254, 225)
#define COLOR_CARD_LINE				RGB(119, 35, 173) // RGB(141, 21, 151)
#define COLOR_CARD_BUTTON_NORMAL	RGB(255, 255, 255)
#define COLOR_CARD_BUTTON_MARKED	RGB(250, 225, 200)
#define COLOR_GRAPHIC_MARKED		RGB(208, 209, 212) // RGB(0, 158, 235)
#define COLOR_GRAPHIC_LINE			RGB(0, 0, 0)

// Timer
#define TIMER_OBJ_ID				100
#define TIMER_OBJ_ELAPSE			100
#define TIMER_MOVE_ID				101
#define TIMER_MOVE_ELAPSE			50	// frequência da atualização (mover)
#define TIMER_LEFT_ID				102
#define TIMER_RIGHT_ID				103
#define TIMER_TOP_ID				104
#define TIMER_BOTTOM_ID				105
#define TIMER_DIAG_A_ID				106
#define TIMER_DIAG_B_ID				107
#define TIMER_DIAG_C_ID				108
#define TIMER_DIAG_D_ID				109
#define TIMER_RESIZE_ELAPSE			20	// frequência da atualização (redimensionar)
#define TIMER_TOTAL_ID				110
#define TIMER_TOTAL_ELAPSE			30	// frequência de suspensão processamento
#define TIMER_EXEC_ID				111
#define TIMER_EXEC_ELAPSE			30
#define TIMER_SUMMARIZE_ID			112
#define TIMER_SUMMARIZE_ELAPSE		30
#define TIMER_GENERATE_IMAGE_ID		113
#define TIMER_GENERATE_IMAGE_ELAPSE	30
#define TIMER_CHECK_ID				114
#define TIMER_CHECK_ELAPSE			30
#define TIMER_MESSAGE_ID1			115
#define TIMER_MESSAGE_ID2			116
#define TIMER_MESSAGE_ID3			117

// Main
#define OBJ_ID_MIN			200
#define OBJ_ID_MAX			201
#define OBJ_ID_FEC			202
#define STATIC_ICON			203
#define PANEL_A				204
#define PANEL_B				205
#define PANEL_C				206
#define PANEL_D				207
#define STATUS_BAR_01		208
#define STATUS_BAR_02		209
#define STATUS_BAR_03		210
#define PROGRESS_01			211
#define PALETTE				212

// Paintel A
#define LISTVIEW_01_A		250
#define BUTTON_01_A			251

// Paintel B
#define LISTVIEW_01_B		300
#define BUTTON_01_B			351

// Paintel C
#define LISTVIEW_01_C		350
#define BUTTON_01_C			351
#define BUTTON_02_C			352
#define BUTTON_03_C			353
#define BUTTON_04_C			354
#define BUTTON_05_C			355
#define BUTTON_06_C			356

// Paintel D
#define TABCONTROL_01_D		400

#define EXT_A				150
#define LISTVIEW_01_D_EXTA	421

#define EXT_B				151
#define BUTTON_01_D_EXTB	441
#define BUTTON_02_D_EXTB	442

#define EXT_C				152
#define LISTVIEW_01_D_EXTC	461
#define BUTTON_01_D_EXTC	462
#define BUTTON_02_D_EXTC	463

#define EXT_D				153
#define STATIC_02_D_EXTD	382
#define STATIC_03_D_EXTD	383
#define STATIC_04_D_EXTD	384
#define CHECKBOX_01_D_EXTD	485
#define CHECKBOX_02_D_EXTD	486
#define CHECKBOX_03_D_EXTD	487
#define CHECKBOX_04_D_EXTD	488
#define CHECKBOX_05_D_EXTD	489
#define CHECKBOX_06_D_EXTD	490
#define CHECKBOX_07_D_EXTD	491
#define CHECKBOX_08_D_EXTD	492
#define CHECKBOX_09_D_EXTD	493
#define CHECKBOX_10_D_EXTD	494
#define CHECKBOX_11_D_EXTD	495
#define CHECKBOX_12_D_EXTD	496
#define CHECKBOX_13_D_EXTD	497
#define CHECKBOX_14_D_EXTD	498
#define CHECKBOX_15_D_EXTD	499
#define CHECKBOX_16_D_EXTD	500
#define CHECKBOX_17_D_EXTD	501
#define CHECKBOX_18_D_EXTD	502
#define CHECKBOX_19_D_EXTD	503
#define CHECKBOX_20_D_EXTD	504
#define CHECKBOX_21_D_EXTD	505
#define CHECKBOX_22_D_EXTD	506
#define CHECKBOX_23_D_EXTD	507
#define CHECKBOX_24_D_EXTD	508
#define CHECKBOX_25_D_EXTD	509
#define CHECKBOX_26_D_EXTD	510
#define CHECKBOX_27_D_EXTD	511
#define CHECKBOX_28_D_EXTD	512
#define CHECKBOX_29_D_EXTD	513
#define CHECKBOX_30_D_EXTD	514
#define CHECKBOX_31_D_EXTD	515
#define CHECKBOX_32_D_EXTD	516
#define CHECKBOX_33_D_EXTD	517
#define CHECKBOX_34_D_EXTD	518
#define CHECKBOX_35_D_EXTD	519
#define CHECKBOX_36_D_EXTD	520
#define CHECKBOX_37_D_EXTD	521
#define CHECKBOX_38_D_EXTD	522
#define CHECKBOX_39_D_EXTD	523

#define EXT_E				154
#define LISTVIEW_01_D_EXTE	551
#define BUTTON_01_D_EXTE	552
#define BUTTON_02_D_EXTE	553

#define EXT_F				155
#define LISTVIEW_01_D_EXTF	601
#define STATIC_01_F			602
#define STATIC_02_F			603
#define CHECKBOX_01_D_EXTF	605
#define CHECKBOX_02_D_EXTF	606
#define CHECKBOX_03_D_EXTF	607
#define CHECKBOX_04_D_EXTF	608
#define CHECKBOX_05_D_EXTF	609
#define CHECKBOX_06_D_EXTF	610
#define CHECKBOX_07_D_EXTF	611
#define CHECKBOX_08_D_EXTF	612
#define CHECKBOX_09_D_EXTF	613
#define CHECKBOX_10_D_EXTF	614
#define CHECKBOX_11_D_EXTF	615
#define CHECKBOX_12_D_EXTF	616
#define CHECKBOX_13_D_EXTF	617
#define CHECKBOX_14_D_EXTF	618
#define CHECKBOX_15_D_EXTF	619
#define CHECKBOX_16_D_EXTF	620
#define CHECKBOX_17_D_EXTF	621
#define CHECKBOX_18_D_EXTF	622
#define CHECKBOX_19_D_EXTF	623
#define CHECKBOX_20_D_EXTF	624
#define CHECKBOX_21_D_EXTF	625
#define CHECKBOX_22_D_EXTF	626
#define CHECKBOX_23_D_EXTF	627
#define CHECKBOX_24_D_EXTF	628
#define CHECKBOX_25_D_EXTF	629
#define CHECKBOX_26_D_EXTF	630
#define CHECKBOX_27_D_EXTF	631
#define CHECKBOX_28_D_EXTF	632
#define CHECKBOX_29_D_EXTF	633
#define CHECKBOX_30_D_EXTF	634
#define CHECKBOX_31_D_EXTF	635
#define CHECKBOX_32_D_EXTF	636
#define CHECKBOX_33_D_EXTF	637
#define CHECKBOX_34_D_EXTF	638
#define CHECKBOX_35_D_EXTF	639
#define CHECKBOX_36_D_EXTF	640
#define CHECKBOX_37_D_EXTF	641
#define CHECKBOX_38_D_EXTF	642
#define CHECKBOX_39_D_EXTF	643
#define CHECKBOX_40_D_EXTF	644
#define CHECKBOX_41_D_EXTF	645
#define CHECKBOX_42_D_EXTF	646
#define CHECKBOX_43_D_EXTF	647
#define CHECKBOX_44_D_EXTF	648
#define CHECKBOX_45_D_EXTF	649
#define CHECKBOX_46_D_EXTF	650
#define CHECKBOX_47_D_EXTF	651
#define CHECKBOX_48_D_EXTF	652
#define CHECKBOX_49_D_EXTF	653
#define CHECKBOX_50_D_EXTF	654

#define EXT_G				156
#define LISTVIEW_01_D_EXTG	701
#define BUTTON_01_D_EXTG	702
#define BUTTON_02_D_EXTG	703
#define BUTTON_03_D_EXTG	704
#define BUTTON_04_D_EXTG	705
#define BUTTON_05_D_EXTG	706
#define EDIT_01_D_EXTG		707
#define EDIT_02_D_EXTG		708
#define EDIT_03_D_EXTG		709
#define EDIT_04_D_EXTG		710
#define EDIT_05_D_EXTG		711
#define EDIT_06_D_EXTG		712
#define EDIT_07_D_EXTG		713
#define EDIT_08_D_EXTG		714
#define EDIT_09_D_EXTG		715
#define EDIT_10_D_EXTG		716
#define EDIT_11_D_EXTG		717
#define EDIT_12_D_EXTG		718
#define EDIT_13_D_EXTG		719
#define EDIT_14_D_EXTG		720

//-------------------------------------------------->>





