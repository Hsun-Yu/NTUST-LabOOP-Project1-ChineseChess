# NTUST_LabOOP_Project1_ChineseChess

## Game資料結構
```language=C++
class Game
{
public:
	Game();
	~Game();

	void initialize();
	bool getInitialType();
	void newGame();
	void lastGame();
	void display();
private:
	Board board;
	bool whoPlay;	//red true, black false
};
```
## Board資料結構
```language=C++
class Board
{
public:
	Board();
	bool readBoardFile(string);
	vector<vector<Chess>> board;
};
```

## Chess資料結構
```language=C++
class Chess
{
public:
	Chess(int);

	int typeID;		// see showArray
	bool colour;	// black is true, red is false
	string show;	// the word will show on the board

private:
	static string showArray;	// save the word with the order of typeID
};
```


## Distribution
- [X]	棋盤	10%	需要確實表示出：楚河漢界、九宮、黑方1至9、紅方一至九以及棋盤標線。
- [X]	讀/存棋盤	20%	讀取或存取文件(.txt)，文件內容代表棋盤上的棋子位置，內容格式請見下方。
- [X]	棋子走棋	20%(缺一棋種扣3%)	所有棋種的走法，包括防呆(象不過河、塞象眼、卒不後退等等)。
- [X]	棋子吃棋	15%(缺一棋種扣2%)	所有棋種的吃法，包括防呆(包飛吃等等)。必須完成「讀/存棋盤」此項才給分。
- [X]	控棋操作	15%	所有控棋的操作，包括：
  	使用方向鍵移動游標
  	使用Enter選棋
- [X]	戰況顯示	5%	顯示雙方每一手的走法，採用中式記譜法。
- [X]	悔棋	5%	回復至我方上一手前的狀況。
- [X]	遊戲選單	5%	使用Esc叫出選單。
- [X]	遊戲提示	5%(各項佔1%)	遊戲提示包括：
  	選取該棋後的可走棋位置
  	選取該棋後的可吃棋位置
  	目前下棋方為黑或紅方
  	黑或紅方被將軍
  	黑或紅方獲勝
- [X]	美觀	5%	遊戲整體美觀。
- [X]	SC	15%	Something cool，額外實作的特殊功能。上下左右人性化，取消選期，AI，提示自殺，提示將軍的將軍的騎，背景音樂，棋盤顏色
-	
