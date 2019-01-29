#ifndef _player_hpp_
#define _player_hpp_

#include <QImage>
#include <QPoint>
#include <QRect>

struct Player
{
        Player();

        void setRect(int);

        QPoint m_player;
        int m_player_angle;
        QRect bounding_rect;
};

#endif
