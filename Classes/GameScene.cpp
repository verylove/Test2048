/*
 * GameScene.cpp
 *
 *  Created on: 2014��11��7��
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

	//��ʼ����Ϸ����
	colorBack = LayerColor::create(
			Color4B(170,170,170,255),
			GAME_TILED_WIDTH * GAME_COLS + GAME_TILED_BOARD_WIDTH*(GAME_COLS+1),
			GAME_TILED_HEIGHT* GAME_ROWS + GAME_TILED_BOARD_WIDTH*(GAME_ROWS+1)
	);

	//ê�������½� 0��0���ı䵽�м�
	colorBack->ignoreAnchorPointForPosition(false);
	colorBack->setAnchorPoint(Point(0.5,0.5));

	colorBack->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));

	this->addChild(colorBack);


	// ��ʼ��ÿһ������
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

	// ��ʼ��  �߼���������
	for( int i = 0 ; i < GAME_ROWS ; ++i )
	{
		for( int j = 0 ; j < GAME_COLS ; ++j )
		{
			map[i][j] = 0;
		}
	}

	// ����һ��������ֿ�
	newNumberTiled();

	// ��Ļ��������

	// ���������¼�
	auto event = EventListenerTouchOneByOne::create();
	event -> onTouchBegan = [&](Touch *tou , Event *eve){
		// ��¼����λ��
		m_x = tou -> getLocation().x;
		m_y = tou -> getLocation().y;
		m_startMove = true;
		return true;
	};
	event -> onTouchMoved = [&](Touch *tou , Event *eve){
		// ��¼����������λ��
		int x = tou -> getLocation().x;
		int y = tou -> getLocation().y;

		// �����������¼���ʼ�����Ҵ���λ�������10���أ���ʼ�����ƶ��ϲ�
		if( m_startMove==true && ( abs( m_x - x ) > 10 || abs( m_y - y ) >10 ))
		{
			m_startMove = false;
			MOVE_DIR dir;
			// ������ĩ����λ�ã��ж����ĸ������ƶ�
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
	// ��ǰ�������Ӽ����������ǿ��Ի�ȡ��ǰ������ �����¼�
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		event,this);

	return true;
}

/*
 *  ˵��һ����ô�ڿյ�λ����������飺
	���ȣ���ȡ�ж��ٿ�λ�ã�
	Ȼ���������һ������С�ڿ�λ������
	�����趨countΪ0��
	�ӵ�һ��λ�õ����һ��λ�ñ�����
	������λ�ã�count+1��
	�����ڲ���������������ڸ�λ�÷������ֿ�
 */
void GameScene::newNumberTiled()
{
	// ����һ�� ���ֿ��ʵ��
	auto tiled = NumberTiled::create();
	// �ҵ��м������е�λ��
	int freeCount = 16 - m_allTiled.size();

	int num = rand() % freeCount;
	int row = 0,col = 0,count = 0;
	bool find = false;

	// �������֣�һ���ڿհ�����
	for( ; row < GAME_ROWS ; ++row )
	{
		for( col = 0 ; col < GAME_COLS ; ++col )
		{
			if( map[row][col] == 0 )
			{
				// ��¼�հ����������
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

	// ע����colorBack������tiledӴ
	colorBack -> addChild( tiled );
	tiled -> moveTo ( row , col );
	m_allTiled.pushBack(tiled);
	map[ row ][ col ] = m_allTiled.getIndex(tiled)+1;
}


void GameScene::moveAllTiled( MOVE_DIR dir )
{
	// ���ݾ��巽����У���Ӧ������ƶ�
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

	// �ƶ���ɣ���������¿�
	newNumberTiled();
}

/*
 *  ���Ǵ�������һ�������浽 ���浹���ڶ��������棬����������
	ÿ����Ҫ���Լ�����һ����Ӧ�е����ֿ���бȽϣ�
	����������е�mapֵΪ0���򲻹ܼ���
	�����������mapֵ��Ϊ0����ӱ�����Ӧ��һֱ�����������ڶ��е���Ӧ��
	�����������������һ��mapֵΪ0���򽫱�����������һ�л�������ʵ������0��������һ�л��ɱ��У�
	��������������Ϊ���ж���Ϊ0���ж�������ֵ�Ƿ����
	��������������������ȣ���������һ�е���ֵ�������������ֿ��Ƴ�������map��������Ӧ��Ž��иı�
	���������������������ȣ���break
	�߼�����map��Vector��ͬ�������ƣ�
	map�洢���Ǳ�ţ�����������Ǳ�ͼ�ڵڼ��������Ŀ飬���Ȳ����Ŀ飬mapֵΪ1���ڶ���Ϊ2���ȵȣ�
	��Vector�Ǵ洢������ֿ���࣬����������ֿ��λ�ã������ֿ����ֵ�ֵ��

	�����������ƶ����ǽ�������Vector�ô����ǣ����ǲ���Ҫ�����жϣ���ҪȥVector�ң�
	������ͨ��map�����жϵ�ǰλ����û�����ֿ飬
	����������������Ҳ����ܶ࣬����Ч�ʻ�õ���ߡ�
 */
void GameScene::moveUp( )
{
	// �����ƶ����еĿ�
	for( int col = 0 ; col < GAME_COLS ; ++col )
	{
		for( int row = GAME_ROWS - 1 ; row >= 0 ; --row )
		{
			if( map[row][col] > 0 )
			{
				for( int row1 = row ; row1 < GAME_ROWS - 1 ; ++row1 )
				{
					// �Ϸ��ǿյ�  �Ż��ƶ�
					if( map[row1+1][col] == 0 )
					{
						map[row1+1][col] = map[row1][col];
						map[row1][col] = 0;

						m_allTiled.at( map[row1+1][col] - 1 ) -> moveTo( row1+1 , col );
					}
					else
					{
						// �жϣ� �Ƿ��������

						// ��ȡ�����Ǹ��ӵ�����
						int numObj = m_allTiled.at( map[row1+1][col] - 1 ) -> m_number;
						// ��ȡ��ǰ���ӵ�����
						int numNow = m_allTiled.at( map[row1][col] - 1 ) -> m_number;

						// ��������������ͬ
						if( numNow == numObj )
						{
							// ������һ������X2
							m_allTiled.at( map[row1+1][col] - 1 ) -> doubleNumber();
							// ȥ������ǰ���ֿ�
							m_allTiled.at( map[row1][col] - 1 ) -> removeFromParent();
							// ��ȡ��ǰ���ֿ���
							int index = map[row1][col];
							m_allTiled.erase( map[row1][col] - 1 );
							// �������д���index����ı�Ŵ�С
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
							// ����ǰ��������Ϊ0
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
	// �����ƶ����еĿ�
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

							// ������ı��
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
	// �����ƶ����еĿ�
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
							// ������ı��
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
	// �����ƶ����еĿ�
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