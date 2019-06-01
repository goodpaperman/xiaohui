/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jörg König
// All rights reserved
//
// This file is part of the completely free tetris clone "CGTetris".
//
// This is free software.
// You may redistribute it by any means providing it is not sold for profit
// without the authors written consent.
//
// No warrantee of any kind, expressed or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////


#ifndef Piece_h
#define Piece_h



class CPiece {
	protected:
		enum {
			NoOfSquares = 4,
			NoOfDirections = 4
		};

		char	m_chFigure	[ NoOfDirections ]
							[ NoOfSquares    ]
							[ NoOfSquares    ];

		short	m_sDirection;

	protected:
		CPiece() : m_sDirection(0) {
			for( register short d = 0 ; d < NoOfDirections ; d++ )
				for( register short l = 0 ; l < NoOfSquares ; l++ )
					for( register short c = 0 ; c < NoOfSquares ; c++ )
						m_chFigure[ d ][ l ][ c ] = 0 ;
		}

	public:
		virtual ~CPiece() {}

	public:
		int	GetLines() const { return NoOfSquares ; }
		int	GetColumns() const { return NoOfSquares ; }

		BOOL	IsSquare( int nLine, int nCol ) const {
			return m_chFigure	[ m_sDirection ]
								[ nLine        ]
								[ nCol         ] ? TRUE : FALSE ;
		}

		void	Rotate() {
			++m_sDirection ;
			m_sDirection &= NoOfDirections - 1 ;
		}

		void	BackRotate() {
			--m_sDirection ;
			m_sDirection &= NoOfDirections - 1 ;
		}

		virtual short	GetPoints() const = 0;
};


class CLongPiece : public CPiece {
	public:
		CLongPiece() {
			for( register short c = 0 ; c < NoOfSquares ; c++ )
				m_chFigure[0][1][c] = m_chFigure[2][1][c] = 1;
			for( register short l = 0 ; l < NoOfSquares ; l++ )
				m_chFigure[1][l][1] = m_chFigure[3][l][1] = 1;
		}

		virtual short	GetPoints() const { return 2; }
};


class CSquarePiece : public CPiece {
	public:
		CSquarePiece() {
			for( register short d = 0 ; d < NoOfDirections ; d++ )
				m_chFigure[d][1][1] = m_chFigure[d][1][2] =
				m_chFigure[d][2][1] = m_chFigure[d][2][2] = 1;
		}

		virtual short	GetPoints() const { return 1; }
};


class CLShapePiece : public CPiece {
	public:
		CLShapePiece() {
			m_chFigure[0][1][1] =m_chFigure[0][1][2] =m_chFigure[0][1][3] = 1;
			m_chFigure[0][2][3] = 1;
			m_chFigure[1][1][2] =m_chFigure[1][2][2] =m_chFigure[1][3][2] = 1;
			m_chFigure[1][3][1] = 1;
			m_chFigure[2][2][1] =m_chFigure[2][2][2] =m_chFigure[2][2][3] = 1;
			m_chFigure[2][1][1] = 1;
			m_chFigure[3][1][1] =m_chFigure[3][2][1] =m_chFigure[3][3][1] = 1;
			m_chFigure[3][1][2] = 1;
		}

		virtual short	GetPoints() const { return 3; }
};


class CRevLShapePiece : public CPiece {
	public:
		CRevLShapePiece() {
			m_chFigure[0][1][1] =m_chFigure[0][1][2] =m_chFigure[0][1][3] = 1;
			m_chFigure[0][2][1] = 1;
			m_chFigure[1][1][2] =m_chFigure[1][2][2] =m_chFigure[1][3][2] = 1;
			m_chFigure[1][1][1] = 1;
			m_chFigure[2][2][1] =m_chFigure[2][2][2] =m_chFigure[2][2][3] = 1;
			m_chFigure[2][1][3] = 1;
			m_chFigure[3][1][1] =m_chFigure[3][2][1] =m_chFigure[3][3][1] = 1;
			m_chFigure[3][3][2] = 1;
		}

		virtual short	GetPoints() const { return 3; }
};


class CTeeShapePiece : public CPiece {
	public:
		CTeeShapePiece() {
			m_chFigure[0][1][1] =m_chFigure[0][1][2] =m_chFigure[0][1][3] = 1;
			m_chFigure[0][2][2] = 1;
			m_chFigure[1][1][1] =m_chFigure[1][2][1] =m_chFigure[1][3][1] = 1;
			m_chFigure[1][2][2] = 1;
			m_chFigure[2][2][1] =m_chFigure[2][2][2] =m_chFigure[2][2][3] = 1;
			m_chFigure[2][1][2] = 1;
			m_chFigure[3][1][2] =m_chFigure[3][2][2] =m_chFigure[3][3][2] = 1;
			m_chFigure[3][2][1] = 1;
		}

		virtual short	GetPoints() const { return 4; }
};


class CSShapePiece : public CPiece {
	public:
		CSShapePiece() {
			m_chFigure[0][1][2] =m_chFigure[0][2][2] =m_chFigure[0][2][1] = 1;
			m_chFigure[0][3][1] = 1;
			m_chFigure[1][1][0] =m_chFigure[1][1][1] =m_chFigure[1][2][1] = 1;
			m_chFigure[1][2][2] = 1;
			m_chFigure[2][1][2] =m_chFigure[2][2][2] =m_chFigure[2][2][1] = 1;
			m_chFigure[2][3][1] = 1;
			m_chFigure[3][1][0] =m_chFigure[3][1][1] =m_chFigure[3][2][1] = 1;
			m_chFigure[3][2][2] = 1;
		}

		virtual short	GetPoints() const { return 5; }
};


class CRevSShapePiece : public CPiece {
	public:
		CRevSShapePiece() {
			m_chFigure[0][1][1] =m_chFigure[0][2][1] =m_chFigure[0][2][2] = 1;
			m_chFigure[0][3][2] = 1;
			m_chFigure[1][2][1] =m_chFigure[1][2][2] =m_chFigure[1][1][2] = 1;
			m_chFigure[1][1][3] = 1;
			m_chFigure[2][1][1] =m_chFigure[2][2][1] =m_chFigure[2][2][2] = 1;
			m_chFigure[2][3][2] = 1;
			m_chFigure[3][2][1] =m_chFigure[3][2][2] =m_chFigure[3][1][2] = 1;
			m_chFigure[3][1][3] = 1;
		}

		virtual short	GetPoints() const { return 5; }
};


// extended figure set from here on :

class CCrossShapePiece : public CPiece {
	public:
		CCrossShapePiece() {
			m_chFigure[0][1][1] =m_chFigure[0][1][2] =m_chFigure[0][1][3] = 1;
			m_chFigure[0][2][2] =m_chFigure[0][0][2] = 1;
			m_chFigure[1][1][1] =m_chFigure[1][1][2] =m_chFigure[1][1][3] = 1;
			m_chFigure[1][2][2] =m_chFigure[1][0][2] = 1;
			m_chFigure[2][1][1] =m_chFigure[2][1][2] =m_chFigure[2][1][3] = 1;
			m_chFigure[2][2][2] =m_chFigure[2][0][2] = 1;
			m_chFigure[3][1][1] =m_chFigure[3][1][2] =m_chFigure[3][1][3] = 1;
			m_chFigure[3][2][2] =m_chFigure[3][0][2] = 1;
		}

		virtual short	GetPoints() const { return 7; }
};


class CUShapePiece : public CPiece {
	public:
		CUShapePiece() {
			m_chFigure[0][1][1] =m_chFigure[0][1][2] =m_chFigure[0][1][3] = 1;
			m_chFigure[0][2][1] =m_chFigure[0][2][3] = 1;
			m_chFigure[1][1][2] =m_chFigure[1][2][2] =m_chFigure[1][3][2] = 1;
			m_chFigure[1][1][1] =m_chFigure[1][3][1] = 1;
			m_chFigure[2][2][1] =m_chFigure[2][2][2] =m_chFigure[2][2][3] = 1;
			m_chFigure[2][1][3] =m_chFigure[2][1][1] = 1;
			m_chFigure[3][1][1] =m_chFigure[3][2][1] =m_chFigure[3][3][1] = 1;
			m_chFigure[3][3][2] =m_chFigure[3][1][2] = 1;
		}

		virtual short	GetPoints() const { return 6; }
};


class CZShapePiece : public CPiece {
	public:
		CZShapePiece() {
			m_chFigure[0][1][1] =m_chFigure[0][1][2] =m_chFigure[0][1][3] = 1;
			m_chFigure[0][0][1] =m_chFigure[0][2][3] = 1;
			m_chFigure[1][1][2] =m_chFigure[1][2][2] =m_chFigure[1][3][2] = 1;
			m_chFigure[1][1][3] =m_chFigure[1][3][1] = 1;
			m_chFigure[2][2][1] =m_chFigure[2][2][2] =m_chFigure[2][2][3] = 1;
			m_chFigure[2][3][3] =m_chFigure[2][1][1] = 1;
			m_chFigure[3][1][1] =m_chFigure[3][2][1] =m_chFigure[3][3][1] = 1;
			m_chFigure[3][3][0] =m_chFigure[3][1][2] = 1;
		}

		virtual short	GetPoints() const { return 5; }
};


class CRevZShapePiece : public CPiece {
	public:
		CRevZShapePiece() {
			m_chFigure[0][1][1] =m_chFigure[0][1][2] =m_chFigure[0][1][3] = 1;
			m_chFigure[0][0][3] =m_chFigure[0][2][1] = 1;
			m_chFigure[1][1][2] =m_chFigure[1][2][2] =m_chFigure[1][3][2] = 1;
			m_chFigure[1][3][3] =m_chFigure[1][1][1] = 1;
			m_chFigure[2][2][1] =m_chFigure[2][2][2] =m_chFigure[2][2][3] = 1;
			m_chFigure[2][3][1] =m_chFigure[2][1][3] = 1;
			m_chFigure[3][1][1] =m_chFigure[3][2][1] =m_chFigure[3][3][1] = 1;
			m_chFigure[3][1][0] =m_chFigure[3][3][2] = 1;
		}

		virtual short	GetPoints() const { return 5; }
};

#endif	// Piece_h
