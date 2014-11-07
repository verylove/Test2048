/*
 * NumberTiled.cpp
 *
 *  Created on: 2014��11��7��
 *      Author: Yang
 */

#include "NumberTiled.h"
#include "GameDefine.h"

USING_NS_CC;

bool NumberTiled::init()
{
	if( !Node::init() )
	{
		return false;
	}

	// ������
	auto bk = LayerColor::create( Color4B(200,200,200,255),GAME_TILED_WIDTH,GAME_TILED_HEIGHT );
	bk -> setTag( 101 );
	this->addChild(bk);


	// ���ֲ㡪�������һ�����֣������ֵ���7 �����4�������2
	int n = rand()%10;
	this -> m_number = n==7?4:2;
	// �������ֵ�ֵ�����費ͬ��ɫ
	switch ( this -> m_number )
	{
	case 2:	bk -> setColor(Color3B(230,220,210));	break;
	case 4:	bk -> setColor(Color3B(230,210,190));	break;
	default:	break;
	}

	// �������壬�������������������ȥ
	TTFConfig config("HelloKitty.ttf",40);
	auto label = Label::createWithTTF(config, StringUtils::format("%d",this->m_number));
	label -> setPosition(Point(GAME_TILED_WIDTH/2,GAME_TILED_HEIGHT/2));
	label -> setColor(Color3B::BLACK);
	label -> setTag( 102 );
	bk -> addChild( label );


	return true;
}

void NumberTiled::moveTo( int r , int c )
{
	this -> m_row = r;
	this -> m_col = c;
	this -> setPosition(
		Point( m_col * GAME_TILED_WIDTH + GAME_TILED_BOARD_WIDTH * (m_col + 1),
		m_row * GAME_TILED_HEIGHT + GAME_TILED_BOARD_WIDTH * (m_row+1)
		));
}

void NumberTiled::doubleNumber( )
{
	// �����ֿ������ֵ����
	this->m_number = this->m_number*2;

	// ��ȡ������������ֲ�
	auto bk = this -> getChildByTag(101);
	Label *label = (Label *) bk -> getChildByTag(102);

	// �����ֲ�����֣����»���
	label -> setString( StringUtils::format( "%d",m_number) );


	//����ֵ�ô�С���Ա������ػ���ɫ
	switch ( this -> m_number )
	{
	case 2:		bk -> setColor(Color3B(230,220,210));		break;
	case 4:		bk -> setColor(Color3B(230,210,190));		break;
	case 8:		bk -> setColor(Color3B(230,150,100));	label -> setColor(Color3B(255,255,255))	;break;
	case 16:	bk -> setColor(Color3B(230,120,80));	label -> setColor(Color3B(255,255,255))	;break;
	case 32:	bk -> setColor(Color3B(230,100,90));	label -> setColor(Color3B(255,255,255))	;break;
	case 64:	bk -> setColor(Color3B(230,70,60));		label -> setColor(Color3B(255,255,255))	;break;
	case 128:	label -> setScale(0.7f);	bk -> setColor(Color3B(230,190,60));	label -> setColor(Color3B(255,255,255))	;break;
	case 256:	label -> setScale(0.7f);	bk -> setColor(Color3B(230,190,60));	label -> setColor(Color3B(255,255,255))	;break;
	case 512:	label -> setScale(0.7f);	bk -> setColor(Color3B(230,190,60));	label -> setColor(Color3B(255,255,255))	;break;
	case 1024:
	case 2048:	label -> setScale(0.5f);	bk -> setColor(Color3B(210,180,30));	label -> setColor(Color3B(255,255,255))	;break;
	default:	break;
	}
}
