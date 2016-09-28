#include "Level.h"
#include "Graphics.h"
#include "globalVar.h"

#include "tinyxml2.h"

#include <SDL.h>
#include <sstream>

#include <algorithm>
#include <cmath>

using namespace tinyxml2;

Level::Level(){}

Level::~Level(){}

Level::Level(std::string mapName, Vector spawnPoint, Graphics &graphics) :
		_mapName(mapName),
		_spawnPoint(spawnPoint),
		_size(Vector(0,0))
{
	this->loadMap(mapName, graphics);
}


void Level::draw(Graphics &graphics) {
	for (int i = 0; i < this->_tileList.size(); i++) {
		this->_tileList.at(i).draw(graphics);
	}
}

void Level::update(int elapsedTime) {

}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	
	//Parse the .tmx file 
	
	XMLDocument doc;
	std::stringstream stst;
	stst << "Content/Maps/" << mapName << ".tmx";//Exp for mapName = Map1 -> Content/Maps/Map1.tmx
	
	
	
	doc.LoadFile(stst.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	//get width and height of the whole map and store it in _size

	int width, height;

	mapNode->QueryIntAttribute("wdith", &width);
	mapNode->QueryIntAttribute("height", &height);

	this->_size = Vector(width, height);

	//Get the width and heigth of the tiles and store it in _tilesize

	int tileWidth, tileHeight;
	
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);

	this->_tilesize = Vector(tileWidth, tileHeight);

	//Loading the tilesets, parsing thorugh and pushing onto the _tilesets List

	XMLElement* pTileset = mapNode->FirstChildElement("tileset");

	if (pTileset != NULL) {
		while (pTileset) {
			int firstgid;

			const char* source = pTileset->FirstChildElement("image")->Attribute("source");

			std::stringstream ss;
			ss << source;
			
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));

			this->_tilesets.push_back(Tileset(tex, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}


	//Loading the layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");

	if (pLayer != NULL) {
		
		while (pLayer) {
			
			//Loading the data element
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				
				while (pData) {
					//Loading tile element
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						
						int tileCounter = 0;
						while (pTile) {

							//Build each individual tile here
							//if gid is 0, no tile should be drawn. Continue loop
							if (pTile->IntAttribute("gid") == 0) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}

							}

							//Get the tileset for the specific gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							int closest = 0;

							for (int i = 0; i < this->_tilesets.size(); i++) {
								if (this->_tilesets[i].firstGid <= gid) {
									//the tileset we want
									closest = this->_tilesets[i].firstGid;
									tls = this->_tilesets.at(i);
									break;
								}
							}

							//No tileset was found for this gid
							if (tls.firstGid == -1) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}
							}
							

							//Get the position of the Tile in the level
							int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCounter / width);
							Vector finalTilePosition = Vector(xx, yy);

						
							//Calculate the position of the Tile in the Tileset

							int tilesetWidth, tilesetHeight;

							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							
							//x Position
							int tsxx = gid % (tilesetWidth / tileWidth) - 1;
							tsxx *= tileWidth;
							
							
							//y Position
							int tsyy = 0;
							int amt = (gid / (tilesetWidth / tileWidth));
							tsyy = tileHeight * amt;
							
							Vector finalTilesetPosition = Vector(tsxx, tsyy);

							//Build the actual tile and add it to the levels tile list
							Tile tile(tls.Texture, Vector(tileWidth, tileHeight),
								finalTilesetPosition, finalTilePosition);

							this->_tileList.push_back(tile);

							tileCounter++;
							
							pTile = pTile->NextSiblingElement("tile");
						}
					}
					pData = pData->NextSiblingElement("data");
				}
			}
			pLayer = pLayer->NextSiblingElement("layer");
		}
	}

}