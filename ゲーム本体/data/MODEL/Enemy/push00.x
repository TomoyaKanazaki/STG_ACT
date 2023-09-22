xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 81;
 95.45000;42.40733;0.00000;,
 99.01598;51.01636;0.00000;,
 70.01487;51.01636;-70.01487;,
 67.49334;42.40733;-67.49334;,
 107.62500;54.58234;0.00000;,
 76.10236;54.58234;-76.10237;,
 116.23402;51.01636;0.00000;,
 82.18987;51.01636;-82.18987;,
 119.80000;42.40733;0.00000;,
 84.71140;42.40733;-84.71140;,
 116.23402;33.79831;0.00000;,
 82.18987;33.79831;-82.18987;,
 107.62500;30.23233;0.00000;,
 76.10236;30.23233;-76.10237;,
 99.01598;33.79831;0.00000;,
 70.01487;33.79831;-70.01487;,
 95.45000;42.40733;0.00000;,
 67.49334;42.40733;-67.49334;,
 -0.00000;51.01636;-99.01598;,
 -0.00000;42.40733;-95.45000;,
 -0.00000;54.58234;-107.62500;,
 -0.00001;51.01636;-116.23402;,
 -0.00001;42.40733;-119.80000;,
 -0.00001;33.79831;-116.23402;,
 -0.00000;30.23233;-107.62500;,
 -0.00000;33.79831;-99.01598;,
 -0.00000;42.40733;-95.45000;,
 -70.01487;51.01636;-70.01487;,
 -67.49334;42.40733;-67.49334;,
 -76.10237;54.58234;-76.10236;,
 -82.18987;51.01636;-82.18987;,
 -84.71140;42.40733;-84.71140;,
 -82.18987;33.79831;-82.18987;,
 -76.10237;30.23233;-76.10236;,
 -70.01487;33.79831;-70.01487;,
 -67.49334;42.40733;-67.49334;,
 -99.01598;51.01636;0.00001;,
 -95.45000;42.40733;0.00001;,
 -107.62500;54.58234;0.00001;,
 -116.23402;51.01636;0.00001;,
 -119.80000;42.40733;0.00001;,
 -116.23402;33.79831;0.00001;,
 -107.62500;30.23233;0.00001;,
 -99.01598;33.79831;0.00001;,
 -95.45000;42.40733;0.00001;,
 -70.01485;51.01636;70.01488;,
 -67.49333;42.40733;67.49335;,
 -76.10236;54.58234;76.10238;,
 -82.18985;51.01636;82.18988;,
 -84.71138;42.40733;84.71141;,
 -82.18985;33.79831;82.18988;,
 -76.10236;30.23233;76.10238;,
 -70.01485;33.79831;70.01488;,
 -67.49333;42.40733;67.49335;,
 0.00000;51.01636;99.01598;,
 0.00000;42.40733;95.45000;,
 0.00000;54.58234;107.62500;,
 0.00000;51.01636;116.23402;,
 0.00000;42.40733;119.80000;,
 0.00000;33.79831;116.23402;,
 0.00000;30.23233;107.62500;,
 0.00000;33.79831;99.01598;,
 0.00000;42.40733;95.45000;,
 70.01485;51.01636;70.01488;,
 67.49333;42.40733;67.49335;,
 76.10236;54.58234;76.10238;,
 82.18986;51.01636;82.18988;,
 84.71138;42.40733;84.71141;,
 82.18986;33.79831;82.18988;,
 76.10236;30.23233;76.10238;,
 70.01485;33.79831;70.01488;,
 67.49333;42.40733;67.49335;,
 99.01598;51.01636;0.00000;,
 95.45000;42.40733;0.00000;,
 107.62500;54.58234;0.00000;,
 116.23402;51.01636;0.00000;,
 119.80000;42.40733;0.00000;,
 116.23402;33.79831;0.00000;,
 107.62500;30.23233;0.00000;,
 99.01598;33.79831;0.00000;,
 95.45000;42.40733;0.00000;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;46,45,54,55;,
 4;45,47,56,54;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;55,54,63,64;,
 4;54,56,65,63;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;64,63,72,73;,
 4;63,65,74,72;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;;
 
 MeshMaterialList {
  2;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.341961;0.762353;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.520784;0.291765;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  64;
  -1.000000;0.000000;-0.000000;,
  -0.698872;0.715247;-0.000000;,
  -0.000000;1.000000;0.000000;,
  0.698872;0.715247;0.000000;,
  1.000000;0.000000;0.000000;,
  0.698872;-0.715247;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.698872;-0.715247;-0.000000;,
  -0.707107;0.000000;0.707107;,
  -0.494177;0.715247;0.494177;,
  -0.000000;1.000000;-0.000000;,
  0.494177;0.715247;-0.494177;,
  0.707107;0.000000;-0.707107;,
  0.494177;-0.715247;-0.494177;,
  -0.000000;-1.000000;-0.000000;,
  -0.494177;-0.715247;0.494177;,
  0.000000;0.000000;1.000000;,
  0.000000;0.715247;0.698872;,
  0.000000;1.000000;0.000000;,
  0.000000;0.715247;-0.698872;,
  -0.000000;0.000000;-1.000000;,
  0.000000;-0.715247;-0.698872;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.715247;0.698872;,
  0.707107;0.000000;0.707107;,
  0.494177;0.715247;0.494177;,
  0.000000;1.000000;0.000000;,
  -0.494177;0.715247;-0.494177;,
  -0.707107;0.000000;-0.707107;,
  -0.494177;-0.715247;-0.494177;,
  0.000000;-1.000000;0.000000;,
  0.494177;-0.715247;0.494177;,
  1.000000;0.000000;-0.000000;,
  0.698872;0.715247;-0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.698872;0.715247;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.698872;-0.715247;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.698872;-0.715247;-0.000000;,
  0.707107;0.000000;-0.707107;,
  0.494177;0.715247;-0.494177;,
  -0.000000;1.000000;0.000000;,
  -0.494177;0.715247;0.494177;,
  -0.707107;0.000000;0.707107;,
  -0.494177;-0.715247;0.494177;,
  -0.000000;-1.000000;0.000000;,
  0.494177;-0.715247;-0.494177;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.715247;-0.698872;,
  -0.000000;1.000000;0.000000;,
  0.000000;0.715247;0.698872;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.715247;0.698872;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-0.715247;-0.698872;,
  -0.707107;0.000000;-0.707107;,
  -0.494177;0.715247;-0.494177;,
  -0.000000;1.000000;-0.000000;,
  0.494177;0.715247;0.494177;,
  0.707107;0.000000;0.707107;,
  0.494177;-0.715247;0.494177;,
  -0.000000;-1.000000;-0.000000;,
  -0.494177;-0.715247;-0.494177;;
  64;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,40,48,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,48,56,63;,
  4;56,57,1,0;,
  4;57,58,2,1;,
  4;58,59,3,2;,
  4;59,60,4,3;,
  4;60,61,5,4;,
  4;61,62,6,5;,
  4;62,63,7,6;,
  4;63,56,0,7;;
 }
 MeshTextureCoords {
  81;
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;;
 }
}
