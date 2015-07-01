/*
 * HexGrid.h
 *
 *  Created on: May 31, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_HEXGRID_H_
#define HEXSUM_HEXGRID_H_

#include <vector>
#include "Hex.h"

class HexGrid {
public:
	HexGrid(int n, int m);
	void PopulateGrid();
	Hex& At(int q, int r);
	Hex& At(int indice);
	const int n, m;
	int size();
	Hex& GetNeighbor(Hex hex, int direction);
	static Hex Hex_Add(Hex a, Hex b);
	static vector<Hex> hex_directions;
	void GridUpdate();
	void GridRender();
	void UnHighlightAll();
	bool HexValido(Hex hex);
private:
	std::vector<Hex> hexagons;

	int RecursivaBR(int b, int r);
};



#endif /* HEXSUM_HEXGRID_H_ */
