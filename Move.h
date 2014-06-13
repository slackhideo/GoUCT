/* Move.h */

#ifndef __MOVE_H__
#define __MOVE_H__

class Move {
	private:
		int x;
		int y;

	public:
		Move(int x, int y);
		virtual ~Move();
		int getX() const;
		int getY() const;
};

#endif /*__MOVE_H__*/
