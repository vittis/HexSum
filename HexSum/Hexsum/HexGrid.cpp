/*
/*
 * HexGrid.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Vitor
 */

#include "HexGrid.h"
#include <algorithm>

vector<Hex> HexGrid::hex_directions;

HexGrid::HexGrid(int _n, int _m) : n(_n), m(_m) {
	PopulateGrid();
	hex_directions.emplace_back(Hex(1,0));
	hex_directions.emplace_back(Hex(1,-1));
	hex_directions.emplace_back(Hex(0,-1));
	hex_directions.emplace_back(Hex(-1,0));
	hex_directions.emplace_back(Hex(-1,1));
	hex_directions.emplace_back(Hex(0,1));

}
bool HexGrid::HexValido(Hex hex) {
	if (hex.GetQ() > (n-1) || hex.GetQ() < -(n-1))
		return false;
	else {
		if (hex.GetR() >= max(-m-hex.GetQ(), -m) && hex.GetR() <= min(m-hex.GetQ(), m))
			return true;
		else
			return false;
	}
}
void HexGrid::PopulateGrid() {
	int k = n;
    int vezesQueRepete = n - m;
    int delimitador;
    bool chegouLimite = false;
    for (int i = 0; i < n+m-1; i++) {
    	for (int j = 0; j < k; j++) {
    		delimitador=i;
    		if (i >= n)
    			delimitador = n - 1;
    		hexagons.emplace_back(Hex(j-delimitador, i-((n+m)/2-1)));
    		}
    		if (k<=n+m-1 && !chegouLimite) {
    			k++;
            if (k==n+m-1)
            	chegouLimite=true;
    		}
            else {
            	if (vezesQueRepete <= 0) {
            		k--;
            }
            vezesQueRepete--;
        }
    }
}
void HexGrid::UnHighlightAll() {
	for (int i=0; i < (int) hexagons.size() ; i++) {
		hexagons[i].UnHighlight();
	}
}
Hex& HexGrid::GetNeighbor(Hex hex, int direction) {
	Hex _hex = Hex_Add(hex_directions[direction], hex);
	return At(_hex.GetQ(), _hex.GetR());
}

Hex HexGrid::Hex_Add(Hex a, Hex b) {
    return Hex(a.GetQ() + b.GetQ(), a.GetR() + b.GetR());
}

Hex& HexGrid::At(int indice) {
	return hexagons[indice];
}

Hex& HexGrid::At(int q, int r) {
	if (HexValido(Hex(q, r)))
		return hexagons[n*(m+r) + RecursivaBR(m, r) + max(r, 0) + q];
	Hex hex(30,30);
	return hex;
}

int HexGrid::size() {
	return hexagons.size();
}

int HexGrid::RecursivaBR(int b, int r) {
	if (r == -b)
		return 0;
	return abs(abs(b)-abs(r)) + RecursivaBR(b, r-1);
}

void HexGrid::GridRender(){
	for (int i=0; i < (int) hexagons.size() ; i++) {
		hexagons[i].Render();
	}
}

void HexGrid::GridUpdate(){
	for (int i=0; i < (int) hexagons.size() ; i++) {
		hexagons[i].Update();
	}
}
