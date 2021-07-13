#include "Model.h"

#include "Clipping.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>

Model::Model(const char* meshPath, const char* texturePath)
	:texture(*textureFromFile(texturePath))
{
	std::vector<Vec2> textureCoords;
	std::ifstream file(meshPath);
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == 'v') {
			if (line[1] == ' ') { 
				vertices.push_back(Vec3());
				Vec3& vertex = vertices.back();
				char* begin = line.c_str() + 2;
				vertex.x = std::strtof(begin, &end);
				begin = end;
				vertex.y = std::strtof(begin, &end);
				begin = end;
				vertex.z = std::strtof(begin, &end);
			}
			else if(line[1] == 'n') {
				normals.push_back(Vec3());
				Vec3& normal = normals.back();
				char* begin = line.c_str() + 3;
				char* end;
				normal.x = std::strtof(begin, &end);
				begin = end;
				normal.y = std::strtof(begin, &end);
				begin = end;
				normal.z = std::strtof(begin, &end);
			}
			else if (line[1] == 't') {
				textureCoords.push_back(Vec2());
				Vec2& coord = textureCoords.back();
				char* begin = line.c_str() + 3;
				char* end;
				coord.u = std::strtof(begin, &end);
				begin = end;
				coord.v = std::strtof(begin, &end);
			}
		}
		else if (line[0] == 'f') {
			faces.push_back(Face());
			Face& face = faces.back();
			int aUVIndex, bUVIndex, cUVIndex;
			char* begin = line.c_str() + 2;
			char* end;

			face.a = std::strtof(begin, &end);
			begin = end;
			aUVIndex = std::strtol(begin, &end);
			begin = end;
			//Skip normals
			begin = line.find_first_of(' ', begin - line.c_str());

			face.b = std::strtof(begin, &end);
			begin = end;
			bUVIndex = std::strtol(begin, &end);
			begin = end;
			begin = line.find_first_of(' ', begin - line.c_str());
			
			face.c = std::strtof(begin, &end);
			begin = end;
			cUVIndex = std::strtol(begin, &end);
			begin = end;
			begin = line.find_first_of(' ', begin - line.c_str());
			
			// Indices in obj file are 1-based, adjust to 0-based indices
			face.a--;
			face.b--;
			face.c--;
			face.aUV = textureCoords[aUVIndex - 1];
			face.bUV = textureCoords[bUVIndex - 1];
			face.cUV = textureCoords[cUVIndex - 1];
			face.aUV.y = 1.0f - face.aUV.y; // Adjust so (0, 0) is at top left and (1, 1) at bottom right for tex coords
			face.bUV.y = 1.0f - face.bUV.y;
			face.cUV.y = 1.0f - face.cUV.y;
		}
	}
}

