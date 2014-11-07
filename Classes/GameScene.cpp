/*
 * GameScene.cpp
 *
 *  Created on: 2014年11月7日
 *      Author: Yang
 */

#include "GameScene.h"


USING_NS_CC;



Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	//初始化游戏网格
	colorBack = LayerColor::create(
			Color4B(170,170,170,255),
			GAME_TILED_WIDTH * GAME_COLS + GAME_TILED_BOARD_WIDTH*(GAME_COLS+1),
			GAME_TILED_HEIGHT* GAME_ROWS + GAME_TILED_BOARD_WIDTH*(GAME_ROWS+1)
	);

	//锚点在左下角 0，0，改变到中间
	colorBack->ignoreAnchorPointForPosition(false);
	colorBack->setAnchorPoint(Point(0.5,0.5));

	colorBack->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));

	this->addChild(colorBack);


	// 初始化每一个网格
	for( int row = 0 ; row < GAME_ROWS ; ++row )
	{
		for( int col = 0 ; col < GAME_COLS ; ++col )
		{
			auto layerTiled = LayerColor::create(
				Color4B(70,70,70,80),
				GAME_TILED_WIDTH,
				GAME_TILED_HEIGHT);
			layerTiled->setPosition(
				Point(GAME_TILED_WIDTH*col+GAME_TILED_BOARD_WIDTH*(col+1),
				GAME_TILED_HEIGHT*row+GAME_TILED_BOARD_WIDTH*(row+1)));
			colorBack->addChild(layerTiled);
		}
	}

	// 初始化  逻辑网格数组
	for( int i = 0 ; i < GAME_ROWS ; ++i )
	{
		for( int j = 0 ; j < GAME_COLS ; ++j )
		{
			map[i][j] = 0;
		}
	}

	// 产生一个随机数字块
	newNumberTiled();

	// 屏幕触摸处理

	// 创建触摸事件
	auto event = EventListenerTouchOneByOne::create();
	event -> onTouchBegan = [&](Touch *tou , Event *eve){
		// 记录触摸位置
		m_x = tou -> getLocation().x;
		m_y = tou -> getLocation().y;
		m_startMove = true;
		return true;
	};
	event -> onTouchMoved = [&](Touch *tou , Event *eve){
		// 记录触摸结束的位置
		int x = tou -> getLocation().x;
		int y = tou -> getLocation().y;

		// 如果这个触摸事件开始，并且触摸位置相差有10像素，则开始进行移动合并
		if( m_startMove==true && ( abs( m_x - x ) > 10 || abs( m_y - y ) >10 ))
		{
			m_startMove = false;
			MOVE_DIR dir;
			// 根据起末坐标位置，判断向哪个方向移动
			if( abs(m_x - x) > abs(m_y - y) )
			{
				if( m_x < x )
					dir = MOVE_DIR::RIGHT;
				else
					dir = MOVE_DIR::LEFT;
			}
			else
			{
				if( m_y < y )
					dir = MOVE_DIR::UP;
				else
					dir = MOVE_DIR::DOWN;
			}

			moveAllTiled(dir);
		}
	};
	// 当前场景添加监听器，就是可以获取当前场景的 触摸事件
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		event,this);

	return true;
}

/*
 *  说明一下怎么在空的位置随机产生块：
	首先，获取有多少空位置，
	然后，随机产生一个数，小于空位置总数
	接着设定count为0，
	从第一个位置到最后一个位置遍历，
	遇到空位置，count+1，
	若大于产生的随机数，就在该位置放置数字块
 */
void GameScene::newNumberTiled()
{
	// 创建一个 数字块的实例
	auto tiled = NumberTiled::create();
	// 找到有几个空闲的位置
	int freeCount = 16 - m_allTiled.size();

	int num = rand() % freeCount;
	int row = 0,col = 0,count = 0;
	bool find = false;

	// 产生数字，一定在空白区域
	for( ; row < GAME_ROWS ; ++row )
	{
		for( col = 0 ; col < GAME_COLS ; ++col )
		{
			if( map[row][col] == 0 )
			{
				// 记录空白区域的数量
				++count;
				if( count >= num )
				{
					find = true;
					break;
				}
			}
		}
		if( find )
		{
			break;
		}
	}

	// 注意在colorBack中添加tiled哟
	colorBack -> addChild( tiled );
	tiled -> moveTo ( row , col );
	m_allTiled.pushBack(tiled);
	map[ row ][ col ] = m_allTiled.getIndex(tiled)+1;
}


void GameScene::moveAllTiled( MOVE_DIR dir )
{
	// 根据具体方向进行，相应方向的移动
	switch ( dir )
	{
	case MOVE_DIR::UP:	moveUp();
		break;
	case MOVE_DIR::DOWN:	moveDown();
		break;
	case MOVE_DIR::LEFT:	moveLeft();
		break;
	case MOVE_DIR::RIGHT:	moveRight();
		break;
	default:
		break;
	}

	// 移动完成，随机产生新块
	newNumberTiled();
}

/*
 *  就是从最下面一行最左面到 上面倒数第二行最右面，挨个遍历，
	每个都要和自己上面一行相应列的数字块进行比较，
	——如果本行的map值为0，则不管继续
	——如果本行map值不为0，则从本行相应列一直遍历到倒数第二行的相应列
	————如果上面那一行map值为0，则将本行与上面那一行互换（其实本行置0，上面那一行换成本行）
	————否则，因为两行都不为0，判断两行数值是否相等
	————————若相等，则上面那一行的数值翻倍，本行数字块移除，并对map内其他相应编号进行改变
	————————若不等，则break
	逻辑块由map和Vector共同处理控制，
	map存储的是编号，就是这个块是本图内第几个产生的块，最先产生的块，map值为1，第二个为2，等等，
	而Vector是存储这个数字块的类，包括这个数字块的位置，和数字块数字的值。

	用这两个控制而不是仅仅单用Vector好处就是，我们不需要遇到判断，就要去Vector找，
	而是先通过map可以判断当前位置有没有数字块，
	而且在随机生成那里，也方便很多，程序效率会得到提高。
 */
void GameScene::moveUp( )
{
	// 向上移动所有的块
	for( int col = 0 ; col < GAME_COLS ; ++col )
	{
		for( int row = GAME_ROWS - 1 ; row >= 0 ; --row )
		{
			if( map[row][col] > 0 )
			{
				for( int row1 = row ; row1 < GAME_ROWS - 1 ; ++row1 )
				{
					// 上方是空的  才会移动
					if( map[row1+1][col] == 0 )
					{
						map[row1+1][col] = map[row1][col];
						map[row1][col] = 0;

						m_allTiled.at( map[row1+1][col] - 1 ) -> moveTo( row1+1 , col );
					}
					else
					{
						// 判断， 是否可以消除

						// 获取上面那格子的数字
						int numObj = m_allTiled.at( map[row1+1][col] - 1 ) -> m_number;
						// 获取当前格子的数字
						int numNow = m_allTiled.at( map[row1][col] - 1 ) -> m_number;

						// 两个格子数字相同
						if( numNow == numObj )
						{
							// 上面那一行数字X2
							m_allTiled.at( map[row1+1][col] - 1 ) -> doubleNumber();
							// 去除掉当前数字块
							m_allTiled.at( map[row1][col] - 1 ) -> removeFromParent();
							// 获取当前数字块编号
							int index = map[row1][col];
							m_allTiled.erase( map[row1][col] - 1 );
							// 纠正所有大于index号码的编号大小
							for( int r = 0 ; r < GAME_ROWS ; ++r )
							{
								for( int c = 0 ; c < GAME_COLS ; ++c )
								{
									if( map[r][c] > index )
									{
										--map[r][c];
									}
								}
							}
							// 将当前块编号设置为0
							map[row1][col] = 0;
						}
						break;
					}
				}
			}
		}
	}
}

void GameScene::moveDown( )
{
	// 向下移动所有的块
	for( int col = 0 ; col < GAME_COLS ; ++col )
	{
		for( int row = 0 ; row < GAME_ROWS ; ++row )
		{
			if( map[row][col] > 0 )
			{
				for( int row1 = row ; row1 > 0 ; --row1 )
				{
					if( map[row1-1][col] == 0 )
					{
						map[row1-1][col] = map[row1][col];
						map[row1][col] = 0;
						m_allTiled.at( map[row1-1][col] - 1 ) -> moveTo( row1-1 , col );
					}
					else
					{
						int numObj = m_allTiled.at( map[row1-1][col] - 1 ) -> m_number;
						int numNow = m_allTiled.at( map[row1][col] - 1 ) -> m_number;
						if( numNow == numObj )
						{
							m_allTiled.at( map[row1-1][col] - 1 ) -> doubleNumber();
							m_allTiled.at( map[row1][col] - 1 ) -> removeFromParent();

							int index = map[row1][col];
							m_allTiled.erase( map[row1][col] - 1 );

							// 纠正块的编号
							for( int r = 0 ; r < GAME_ROWS ; ++r )
							{
								for( int c = 0 ; c < GAME_COLS ; ++c )
								{
									if( map[r][c] > index )
									{
										--map[r][c];
									}
								}
							}
							map[row1][col] = 0;
						}
						break;
					}
				}
			}
		}
	}
}

void GameScene::moveLeft( )
{
	// 向左移动所有的块
	for( int row = 0 ; row < GAME_ROWS ; ++row )
	{
		for( int col = 0 ; col < GAME_COLS ; ++col )
		{
			if( map[row][col] > 0 )
			{
				for( int col1 = col ; col1 > 0 ; --col1 )
				{
					if( map[row][col1-1] == 0 )
					{
						map[row][col1-1] = map[row][col1];
						map[row][col1] = 0;

						m_allTiled.at( map[row][col1-1] - 1 ) -> moveTo( row , col1-1 );
					}
					else
					{
						int numObj = m_allTiled.at( map[row][col1-1] - 1 ) -> m_number;
						int numNow = m_allTiled.at( map[row][col1] - 1 ) -> m_number;
						if( numNow == numObj )
						{
							m_allTiled.at( map[row][col1-1] - 1 ) -> doubleNumber();
							m_allTiled.at( map[row][col1] - 1 ) -> removeFromParent();
							int index = map[row][col1];
							m_allTiled.erase( map[row][col1] - 1 );
							// 纠正块的编号
							for( int r = 0 ; r < GAME_ROWS ; ++r )
							{
								for( int c = 0 ; c < GAME_COLS ; ++c )
								{
									if( map[r][c] > index )
									{
										--map[r][c];
									}
								}
							}
							map[row][col1] = 0;
						}
						break;
					}
				}
			}
		}
	}
}

void GameScene::moveRight( )
{
	// 向右移动所有的块
	for( int row = 0 ; row < GAME_ROWS ; ++row )
	{
		for( int col = GAME_COLS - 1 ; col >= 0 ; --col )
		{
			if( map[row][col] > 0 )
			{
				for( int col1 = col ; col1 < GAME_COLS - 1 ; ++col1 )
				{
					if( map[row][col1+1] == 0 )
					{
						map[row][col1+1] = map[row][col1];
						map[row][col1] = 0;

						m_allTiled.at( map[row][col1+1] - 1 ) -> moveTo( row , col1+1 );
					}
					else
					{
						int numObj = m_allTiled.at( map[row][col1+1] - 1 ) -> m_number;
						int numNow = m_allTiled.at( map[row][col1] - 1 ) -> m_number;
						if( numNow == numObj )
						{
							m_allTiled.at( map[row][col1+1] - 1 ) -> doubleNumber();
							m_allTiled.at( map[row][col1] - 1 ) -> removeFromParent();
							int index = map[row][col1];
							m_allTiled.erase( map[row][col1] - 1 );

							for( int r = 0 ; r < GAME_ROWS ; ++r )
							{
								for( int c = 0 ; c < GAME_COLS ; ++c )
								{
									if( map[r][c] > index )
									{
										--map[r][c];
									}
								}
							}
							map[row][col1] = 0;
						}
						break;
					}
				}
			}
		}
	}
}
