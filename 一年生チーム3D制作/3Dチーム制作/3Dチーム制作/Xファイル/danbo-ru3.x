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
 361;
 -3.22883;1.32296;-2.39400;,
 -3.22883;1.98191;-2.39400;,
 -2.15255;1.98191;-2.39400;,
 -2.15255;1.32296;-2.39400;,
 -3.22883;2.64086;0.59850;,
 -3.22883;2.64086;1.19700;,
 -2.15255;2.64086;1.19700;,
 -2.15255;2.64086;0.59850;,
 -3.22883;1.98191;2.39400;,
 -3.22883;1.32296;2.39400;,
 -2.15255;1.32296;2.39400;,
 -2.15255;1.98191;2.39400;,
 -3.22883;0.00506;1.19700;,
 -3.22883;0.00506;0.59850;,
 -2.15255;0.00506;0.59850;,
 -2.15255;0.00506;1.19700;,
 -4.30511;1.98191;1.19700;,
 -4.30511;1.98191;0.59850;,
 -4.30511;1.32296;0.59850;,
 -4.30511;1.32296;1.19700;,
 4.30511;1.32296;0.59850;,
 4.30511;1.98191;0.59850;,
 4.30511;1.98191;1.19700;,
 4.30511;1.32296;1.19700;,
 1.07628;0.00506;1.19700;,
 1.07628;0.00506;0.59850;,
 2.15255;0.00506;0.59850;,
 2.15255;0.00506;1.19700;,
 1.07628;1.98191;2.39400;,
 1.07628;1.32296;2.39400;,
 2.15255;1.32296;2.39400;,
 2.15255;1.98191;2.39400;,
 1.07628;2.64086;0.59850;,
 1.07628;2.64086;1.19700;,
 2.15255;2.64086;1.19700;,
 2.15255;2.64086;0.59850;,
 1.07628;1.32296;-2.39400;,
 1.07628;1.98191;-2.39400;,
 2.15255;1.98191;-2.39400;,
 2.15255;1.32296;-2.39400;,
 1.07628;2.64086;-1.19700;,
 1.07628;2.64086;-0.59850;,
 2.15255;2.64086;-0.59850;,
 2.15255;2.64086;-1.19700;,
 -3.22883;2.64086;-1.19700;,
 -3.22883;2.64086;-0.59850;,
 -2.15255;2.64086;-0.59850;,
 -2.15255;2.64086;-1.19700;,
 -4.30511;1.32296;-0.59850;,
 -4.30511;1.98191;-0.59850;,
 -4.30511;1.98191;-1.19700;,
 -4.30511;1.32296;-1.19700;,
 -3.22883;0.00506;-0.59850;,
 -3.22883;0.00506;-1.19700;,
 -2.15255;0.00506;-1.19700;,
 -2.15255;0.00506;-0.59850;,
 1.07628;0.00506;-0.59850;,
 1.07628;0.00506;-1.19700;,
 2.15255;0.00506;-1.19700;,
 2.15255;0.00506;-0.59850;,
 4.30511;1.98191;-1.19700;,
 4.30511;1.98191;-0.59850;,
 4.30511;1.32296;-0.59850;,
 4.30511;1.32296;-1.19700;,
 3.22883;0.00506;-1.19700;,
 3.22883;0.00506;-0.59850;,
 3.22883;0.00506;0.59850;,
 3.22883;0.00506;1.19700;,
 3.22883;1.32296;2.39400;,
 3.22883;1.98191;2.39400;,
 3.22883;2.64086;1.19700;,
 3.22883;2.64086;0.59850;,
 3.22883;2.64086;-0.59850;,
 3.22883;2.64086;-1.19700;,
 3.22883;1.98191;-2.39400;,
 3.22883;1.32296;-2.39400;,
 -1.07628;0.00506;-1.19700;,
 -1.07628;0.00506;-0.59850;,
 -1.07628;0.00506;0.59850;,
 -1.07628;0.00506;1.19700;,
 -1.07628;1.32296;2.39400;,
 -1.07628;1.98191;2.39400;,
 -1.07628;2.64086;1.19700;,
 -1.07628;2.64086;0.59850;,
 -1.07628;2.64086;-0.59850;,
 -1.07628;2.64086;-1.19700;,
 -1.07628;1.98191;-2.39400;,
 -1.07628;1.32296;-2.39400;,
 3.22883;2.64086;-1.79550;,
 2.15255;2.64086;-1.79550;,
 1.07628;2.64086;-1.79550;,
 -1.07628;2.64086;-1.79550;,
 -2.15255;2.64086;-1.79550;,
 -3.22883;2.64086;-1.79550;,
 -4.30511;1.98191;-1.79550;,
 -4.30511;1.32296;-1.79550;,
 -3.22883;0.00506;-1.79550;,
 -2.15255;0.00506;-1.79550;,
 -1.07628;0.00506;-1.79550;,
 1.07628;0.00506;-1.79550;,
 2.15255;0.00506;-1.79550;,
 3.22883;0.00506;-1.79550;,
 4.30511;1.32296;-1.79550;,
 4.30511;1.98191;-1.79550;,
 3.22883;0.00506;1.79550;,
 2.15255;0.00506;1.79550;,
 1.07628;0.00506;1.79550;,
 -1.07628;0.00506;1.79550;,
 -2.15255;0.00506;1.79550;,
 -3.22883;0.00506;1.79550;,
 -4.30511;1.32296;1.79550;,
 -4.30511;1.98191;1.79550;,
 -3.22883;2.64086;1.79550;,
 -2.15255;2.64086;1.79550;,
 -1.07628;2.64086;1.79550;,
 1.07628;2.64086;1.79550;,
 2.15255;2.64086;1.79550;,
 3.22883;2.64086;1.79550;,
 4.30511;1.98191;1.79550;,
 4.30511;1.32296;1.79550;,
 3.22883;0.66401;-2.39400;,
 2.15255;0.66401;-2.39400;,
 1.07628;0.66401;-2.39400;,
 -1.07628;0.66401;-2.39400;,
 -2.15255;0.66401;-2.39400;,
 -3.22883;0.66401;-2.39400;,
 -4.30511;0.66401;-1.79550;,
 -4.30511;0.66401;-1.19700;,
 -4.30511;0.66401;-0.59850;,
 -4.30511;0.66401;0.59850;,
 -4.30511;0.66401;1.19700;,
 -4.30511;0.66401;1.79550;,
 -3.22883;0.66401;2.39400;,
 -2.15255;0.66401;2.39400;,
 -1.07628;0.66401;2.39400;,
 1.07628;0.66401;2.39400;,
 2.15255;0.66401;2.39400;,
 3.22883;0.66401;2.39400;,
 4.30511;0.66401;1.79550;,
 4.30511;0.66401;1.19700;,
 4.30511;0.66401;0.59850;,
 4.30511;0.66401;-0.59850;,
 4.30511;0.66401;-1.19700;,
 4.30511;0.66401;-1.79550;,
 3.22883;2.64086;2.39400;,
 2.15255;2.64086;2.39400;,
 1.07628;2.64086;2.39400;,
 -1.07628;2.64086;2.39400;,
 -2.15255;2.64086;2.39400;,
 -3.22883;2.64086;2.39400;,
 -4.30511;2.64086;1.19700;,
 -4.30511;2.64086;1.79550;,
 -4.30511;2.64086;0.59850;,
 -4.30511;2.64086;-1.19700;,
 -4.30511;2.64086;-0.59850;,
 -4.30511;2.64086;-1.79550;,
 -2.15255;2.64086;-2.39400;,
 -3.22883;2.64086;-2.39400;,
 -1.07628;2.64086;-2.39400;,
 2.15255;2.64086;-2.39400;,
 1.07628;2.64086;-2.39400;,
 3.22883;2.64086;-2.39400;,
 4.30511;2.64086;-1.19700;,
 4.30511;2.64086;-1.79550;,
 4.30511;2.64086;-0.59850;,
 4.30511;2.64086;1.19700;,
 4.30511;2.64086;0.59850;,
 4.30511;2.64086;1.79550;,
 3.22883;0.00506;-2.39400;,
 2.15255;0.00506;-2.39400;,
 1.07628;0.00506;-2.39400;,
 -1.07628;0.00506;-2.39400;,
 -2.15255;0.00506;-2.39400;,
 -3.22883;0.00506;-2.39400;,
 -4.30511;0.00506;-1.79550;,
 -4.30511;0.00506;-1.19700;,
 -4.30511;0.00506;-0.59850;,
 -4.30511;0.00506;0.59850;,
 -4.30511;0.00506;1.19700;,
 -4.30511;0.00506;1.79550;,
 -2.15255;0.00506;2.39400;,
 -3.22883;0.00506;2.39400;,
 -1.07628;0.00506;2.39400;,
 2.15255;0.00506;2.39400;,
 1.07628;0.00506;2.39400;,
 3.22883;0.00506;2.39400;,
 4.30511;0.00506;1.79550;,
 4.30511;0.00506;1.19700;,
 4.30511;0.00506;0.59850;,
 4.30511;0.00506;-0.59850;,
 4.30511;0.00506;-1.19700;,
 4.30511;0.00506;-1.79550;,
 1.07628;2.64086;-0.29925;,
 2.15255;2.64086;-0.29925;,
 3.22883;2.64086;-0.29925;,
 4.30511;2.64086;-0.29925;,
 4.30511;1.98191;-0.29925;,
 4.30511;1.32296;-0.29925;,
 4.30511;0.66401;-0.29925;,
 4.30511;0.00506;-0.29925;,
 3.22883;0.00506;-0.29925;,
 2.15255;0.00506;-0.29925;,
 1.07628;0.00506;-0.29925;,
 -1.07628;0.00506;-0.29925;,
 -2.15255;0.00506;-0.29925;,
 -3.22883;0.00506;-0.29925;,
 -4.30511;0.00506;-0.29925;,
 -4.30511;0.66401;-0.29925;,
 -4.30511;1.32296;-0.29925;,
 -4.30511;1.98191;-0.29925;,
 -4.30511;2.64086;-0.29925;,
 -3.22883;2.64086;-0.29925;,
 -2.15255;2.64086;-0.29925;,
 -1.07628;2.64086;-0.29925;,
 3.22883;2.64086;0.29925;,
 2.15255;2.64086;0.29925;,
 1.07628;2.64086;0.29925;,
 -1.07628;2.64086;0.29925;,
 -2.15255;2.64086;0.29925;,
 -3.22883;2.64086;0.29925;,
 -4.30511;2.64086;0.29925;,
 -4.30511;1.98191;0.29925;,
 -4.30511;1.32296;0.29925;,
 -4.30511;0.66401;0.29925;,
 -4.30511;0.00506;0.29925;,
 -3.22883;0.00506;0.29925;,
 -2.15255;0.00506;0.29925;,
 -1.07628;0.00506;0.29925;,
 1.07628;0.00506;0.29925;,
 2.15255;0.00506;0.29925;,
 3.22883;0.00506;0.29925;,
 4.30511;0.00506;0.29925;,
 4.30511;0.66401;0.29925;,
 4.30511;1.32296;0.29925;,
 4.30511;1.98191;0.29925;,
 4.30511;2.64086;0.29925;,
 0.00000;0.00506;-1.79550;,
 0.00000;0.00506;-1.19700;,
 0.00000;0.00506;-0.59850;,
 0.00000;0.00506;-0.29925;,
 0.00000;0.00506;0.59850;,
 0.00000;0.00506;0.29925;,
 0.00000;0.00506;1.19700;,
 0.00000;0.00506;1.79550;,
 0.00000;0.00506;2.39400;,
 0.00000;0.66401;2.39400;,
 0.00000;1.32296;2.39400;,
 0.00000;1.98191;2.39400;,
 0.00000;2.64086;2.39400;,
 0.00000;2.64086;1.79550;,
 0.00000;2.64086;1.19700;,
 0.00000;2.64086;0.59850;,
 0.00000;2.64086;0.29925;,
 0.00000;2.64086;-0.59850;,
 0.00000;2.64086;-0.29925;,
 0.00000;2.64086;-1.19700;,
 0.00000;2.64086;-1.79550;,
 0.00000;2.64086;-2.39400;,
 0.00000;1.98191;-2.39400;,
 0.00000;1.32296;-2.39400;,
 0.00000;0.66401;-2.39400;,
 0.00000;0.00506;-2.39400;,
 -4.30511;1.98191;-2.39400;,
 -4.30511;2.64086;-2.39400;,
 -4.30511;1.32296;-2.39400;,
 -4.30511;0.66401;-2.39400;,
 -4.30511;0.00506;-2.39400;,
 -2.15255;0.00506;-2.39400;,
 -3.22883;0.00506;-2.39400;,
 -1.07628;0.00506;-2.39400;,
 0.00000;0.00506;-2.39400;,
 2.15255;0.00506;-2.39400;,
 1.07628;0.00506;-2.39400;,
 3.22883;0.00506;-2.39400;,
 4.30511;0.66401;-2.39400;,
 4.30511;0.00506;-2.39400;,
 4.30511;1.32296;-2.39400;,
 4.30511;1.98191;-2.39400;,
 4.30511;2.64086;-2.39400;,
 -4.30511;0.66401;2.39400;,
 -4.30511;0.00506;2.39400;,
 -4.30511;1.32296;2.39400;,
 -4.30511;1.98191;2.39400;,
 -4.30511;2.64086;2.39400;,
 4.30511;1.98191;2.39400;,
 4.30511;2.64086;2.39400;,
 4.30511;1.32296;2.39400;,
 4.30511;0.66401;2.39400;,
 4.30511;0.00506;2.39400;,
 -4.30511;0.00506;-0.59850;,
 -4.30511;0.00506;-0.29925;,
 -4.30511;0.00506;-1.19700;,
 -4.30511;0.00506;-1.79550;,
 -4.30511;0.00506;-2.39400;,
 -4.30511;2.64086;-1.79550;,
 -4.30511;2.64086;-1.19700;,
 -4.30511;2.64086;-0.59850;,
 -4.30511;2.64086;-0.29925;,
 -4.30511;2.64086;0.59850;,
 -4.30511;2.64086;0.29925;,
 -4.30511;2.64086;1.19700;,
 -4.30511;2.64086;1.79550;,
 -4.30511;2.64086;2.39400;,
 -4.30511;1.98191;2.39400;,
 -4.30511;1.32296;2.39400;,
 -4.30511;0.66401;2.39400;,
 -4.30511;0.00506;2.39400;,
 -4.30511;0.00506;1.79550;,
 -4.30511;0.00506;1.19700;,
 -4.30511;0.00506;0.59850;,
 -4.30511;0.00506;0.29925;,
 2.15255;2.64086;0.00000;,
 1.07628;2.64086;0.00000;,
 3.22883;2.64086;0.00000;,
 4.30511;2.64086;0.00000;,
 4.30511;1.98191;0.00000;,
 4.30511;1.32296;0.00000;,
 4.30511;0.66401;0.00000;,
 4.30511;0.00506;0.00000;,
 3.22883;0.00506;0.00000;,
 2.15255;0.00506;0.00000;,
 1.07628;0.00506;0.00000;,
 -1.07628;0.00506;0.00000;,
 0.00000;0.00506;0.00000;,
 -2.15255;0.00506;0.00000;,
 -3.22883;0.00506;0.00000;,
 -4.30511;0.00506;0.00000;,
 -4.30511;0.66401;0.00000;,
 -4.30511;0.00506;0.00000;,
 -4.30511;1.32296;0.00000;,
 -4.30511;1.98191;0.00000;,
 -4.30511;2.64086;0.00000;,
 -4.30511;2.64086;0.00000;,
 -3.22883;2.64086;0.00000;,
 -2.15255;2.64086;0.00000;,
 -1.07628;2.64086;0.00000;,
 0.00000;2.64086;0.00000;,
 4.30511;0.00506;-1.79550;,
 4.30511;0.00506;-2.39400;,
 4.30511;0.00506;-1.19700;,
 4.30511;0.00506;-0.59850;,
 4.30511;0.00506;-0.29925;,
 4.30511;0.00506;0.00000;,
 4.30511;0.00506;0.29925;,
 4.30511;0.00506;0.59850;,
 4.30511;0.00506;1.19700;,
 4.30511;0.00506;1.79550;,
 4.30511;0.00506;2.39400;,
 4.30511;0.66401;2.39400;,
 4.30511;1.32296;2.39400;,
 4.30511;1.98191;2.39400;,
 4.30511;2.64086;2.39400;,
 4.30511;2.64086;1.79550;,
 4.30511;2.64086;1.19700;,
 4.30511;2.64086;0.59850;,
 4.30511;2.64086;0.29925;,
 4.30511;2.64086;0.00000;,
 4.30511;2.64086;-0.29925;,
 4.30511;2.64086;-0.59850;,
 4.30511;2.64086;-1.19700;,
 4.30511;2.64086;-1.79550;;
 
 304;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,59,58;,
 4;66,67,27,26;,
 4;68,69,31,30;,
 4;70,71,35,34;,
 4;72,73,43,42;,
 4;74,75,39,38;,
 4;54,76,77,55;,
 4;78,79,15,14;,
 4;10,80,81,11;,
 4;6,82,83,7;,
 4;84,85,47,46;,
 4;2,86,87,3;,
 4;73,88,89,43;,
 4;90,40,43,89;,
 4;91,92,47,85;,
 4;93,44,47,92;,
 4;94,95,51,50;,
 4;53,96,97,54;,
 4;97,98,76,54;,
 4;57,99,100,58;,
 4;101,64,58,100;,
 4;102,103,60,63;,
 4;67,104,105,27;,
 4;106,24,27,105;,
 4;107,108,15,79;,
 4;109,12,15,108;,
 4;110,111,16,19;,
 4;5,112,113,6;,
 4;113,114,82,6;,
 4;33,115,116,34;,
 4;117,70,34,116;,
 4;118,119,23,22;,
 4;75,120,121,39;,
 4;122,36,39,121;,
 4;3,87,123,124;,
 4;125,0,3,124;,
 4;95,126,127,51;,
 4;128,48,51,127;,
 4;19,18,129,130;,
 4;131,110,19,130;,
 4;9,132,133,10;,
 4;133,134,80,10;,
 4;29,135,136,30;,
 4;137,68,30,136;,
 4;119,138,139,23;,
 4;140,20,23,139;,
 4;63,62,141,142;,
 4;143,102,63,142;,
 4;69,144,145,31;,
 4;146,28,31,145;,
 4;11,81,147,148;,
 4;149,8,11,148;,
 4;150,16,111,151;,
 4;152,17,16,150;,
 4;153,50,49,154;,
 4;155,94,50,153;,
 4;156,2,1,157;,
 4;158,86,2,156;,
 4;159,38,37,160;,
 4;161,74,38,159;,
 4;162,60,103,163;,
 4;164,61,60,162;,
 4;165,22,21,166;,
 4;167,118,22,165;,
 4;120,168,169,121;,
 4;170,122,121,169;,
 4;124,123,171,172;,
 4;173,125,124,172;,
 4;126,174,175,127;,
 4;176,128,127,175;,
 4;130,129,177,178;,
 4;179,131,130,178;,
 4;180,133,132,181;,
 4;182,134,133,180;,
 4;183,136,135,184;,
 4;185,137,136,183;,
 4;138,186,187,139;,
 4;188,140,139,187;,
 4;142,141,189,190;,
 4;191,143,142,190;,
 4;41,192,193,42;,
 4;194,72,42,193;,
 4;195,196,61,164;,
 4;62,61,196,197;,
 4;141,62,197,198;,
 4;189,141,198,199;,
 4;65,200,201,59;,
 4;202,56,59,201;,
 4;55,77,203,204;,
 4;204,205,52,55;,
 4;206,207,128,176;,
 4;207,208,48,128;,
 4;208,209,49,48;,
 4;154,49,209,210;,
 4;45,211,212,46;,
 4;212,213,84,46;,
 4;71,214,215,35;,
 4;216,32,35,215;,
 4;7,83,217,218;,
 4;218,219,4,7;,
 4;220,221,17,152;,
 4;18,17,221,222;,
 4;129,18,222,223;,
 4;177,129,223,224;,
 4;13,225,226,14;,
 4;226,227,78,14;,
 4;25,228,229,26;,
 4;230,66,26,229;,
 4;231,232,140,188;,
 4;232,233,20,140;,
 4;233,234,21,20;,
 4;166,21,234,235;,
 4;98,236,237,76;,
 4;77,76,237,238;,
 4;239,203,77,238;,
 4;240,78,227,241;,
 4;242,79,78,240;,
 4;243,107,79,242;,
 4;244,245,134,182;,
 4;80,134,245,246;,
 4;81,80,246,247;,
 4;147,81,247,248;,
 4;114,249,250,82;,
 4;83,82,250,251;,
 4;252,217,83,251;,
 4;253,84,213,254;,
 4;255,85,84,253;,
 4;256,91,85,255;,
 4;257,258,86,158;,
 4;87,86,258,259;,
 4;123,87,259,260;,
 4;171,123,260,261;,
 4;88,161,159,89;,
 4;160,90,89,159;,
 4;158,91,256,257;,
 4;156,92,91,158;,
 4;157,93,92,156;,
 4;262,94,155,263;,
 4;264,95,94,262;,
 4;265,126,95,264;,
 4;266,174,126,265;,
 4;267,97,96,268;,
 4;269,98,97,267;,
 4;270,236,98,269;,
 4;271,100,99,272;,
 4;273,101,100,271;,
 4;274,143,191,275;,
 4;276,102,143,274;,
 4;277,103,102,276;,
 4;163,103,277,278;,
 4;104,185,183,105;,
 4;184,106,105,183;,
 4;182,107,243,244;,
 4;180,108,107,182;,
 4;181,109,108,180;,
 4;279,131,179,280;,
 4;281,110,131,279;,
 4;282,111,110,281;,
 4;151,111,282,283;,
 4;148,113,112,149;,
 4;147,114,113,148;,
 4;248,249,114,147;,
 4;145,116,115,146;,
 4;144,117,116,145;,
 4;284,118,167,285;,
 4;286,119,118,284;,
 4;287,138,119,286;,
 4;288,186,138,287;,
 4;289,52,205,290;,
 4;291,53,52,289;,
 4;292,96,53,291;,
 4;268,96,292,293;,
 4;265,125,173,266;,
 4;264,0,125,265;,
 4;262,1,0,264;,
 4;157,1,262,263;,
 4;294,93,157,263;,
 4;295,44,93,294;,
 4;296,45,44,295;,
 4;297,211,45,296;,
 4;298,4,219,299;,
 4;300,5,4,298;,
 4;301,112,5,300;,
 4;149,112,301,302;,
 4;303,8,149,302;,
 4;304,9,8,303;,
 4;305,132,9,304;,
 4;181,132,305,306;,
 4;307,109,181,306;,
 4;308,12,109,307;,
 4;309,13,12,308;,
 4;310,225,13,309;,
 4;311,193,192,312;,
 4;313,194,193,311;,
 4;314,315,196,195;,
 4;197,196,315,316;,
 4;198,197,316,317;,
 4;199,198,317,318;,
 4;200,319,320,201;,
 4;321,202,201,320;,
 4;322,203,239,323;,
 4;204,203,322,324;,
 4;325,205,204,324;,
 4;290,205,325,326;,
 4;327,207,206,328;,
 4;329,208,207,327;,
 4;330,209,208,329;,
 4;210,209,330,331;,
 4;332,333,211,297;,
 4;212,211,333,334;,
 4;335,213,212,334;,
 4;254,213,335,336;,
 4;214,313,311,215;,
 4;312,216,215,311;,
 4;335,217,252,336;,
 4;218,217,335,334;,
 4;333,219,218,334;,
 4;299,219,333,332;,
 4;331,330,221,220;,
 4;222,221,330,329;,
 4;223,222,329,327;,
 4;224,223,327,328;,
 4;326,325,225,310;,
 4;226,225,325,324;,
 4;322,227,226,324;,
 4;241,227,322,323;,
 4;320,229,228,321;,
 4;319,230,229,320;,
 4;317,232,231,318;,
 4;316,233,232,317;,
 4;315,234,233,316;,
 4;235,234,315,314;,
 4;239,202,321,323;,
 4;238,56,202,239;,
 4;237,57,56,238;,
 4;236,99,57,237;,
 4;272,99,236,270;,
 4;260,122,170,261;,
 4;259,36,122,260;,
 4;258,37,36,259;,
 4;160,37,258,257;,
 4;256,90,160,257;,
 4;255,40,90,256;,
 4;253,41,40,255;,
 4;254,192,41,253;,
 4;312,192,254,336;,
 4;252,216,312,336;,
 4;251,32,216,252;,
 4;250,33,32,251;,
 4;249,115,33,250;,
 4;146,115,249,248;,
 4;247,28,146,248;,
 4;246,29,28,247;,
 4;245,135,29,246;,
 4;184,135,245,244;,
 4;243,106,184,244;,
 4;242,24,106,243;,
 4;240,25,24,242;,
 4;241,228,25,240;,
 4;321,228,241,323;,
 4;337,101,273,338;,
 4;339,64,101,337;,
 4;340,65,64,339;,
 4;341,200,65,340;,
 4;342,319,200,341;,
 4;343,230,319,342;,
 4;344,66,230,343;,
 4;345,67,66,344;,
 4;346,104,67,345;,
 4;347,185,104,346;,
 4;348,137,185,347;,
 4;349,68,137,348;,
 4;350,69,68,349;,
 4;351,144,69,350;,
 4;352,117,144,351;,
 4;353,70,117,352;,
 4;354,71,70,353;,
 4;355,214,71,354;,
 4;356,313,214,355;,
 4;357,194,313,356;,
 4;358,72,194,357;,
 4;359,73,72,358;,
 4;360,88,73,359;,
 4;278,161,88,360;,
 4;277,74,161,278;,
 4;276,75,74,277;,
 4;274,120,75,276;,
 4;275,168,120,274;;
 
 MeshMaterialList {
  2;
  304;
  1,
  0,
  1,
  0,
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
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
  1,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  0,
  0,
  0,
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  0,
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
  0,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  0,
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
  0,
  0,
  0,
  0,
  1,
  1,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "æ/danbo-ru2.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "æ/danbo-ru.jpg";
   }
  }
 }
 MeshNormals {
  6;
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  304;
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;;
 }
 MeshTextureCoords {
  361;
  0.593750;0.125000;,
  0.593750;0.187500;,
  0.562500;0.187500;,
  0.562500;0.125000;,
  0.593750;0.406250;,
  0.593750;0.437500;,
  0.562500;0.437500;,
  0.562500;0.406250;,
  0.593750;0.562500;,
  0.593750;0.625000;,
  0.562500;0.625000;,
  0.562500;0.562500;,
  0.593750;0.812500;,
  0.593750;0.843750;,
  0.562500;0.843750;,
  0.562500;0.812500;,
  0.812500;0.187500;,
  0.781250;0.187500;,
  0.781250;0.125000;,
  0.812500;0.125000;,
  0.218750;0.125000;,
  0.218750;0.187500;,
  0.187500;0.187500;,
  0.187500;0.125000;,
  0.468750;0.812500;,
  0.468750;0.843750;,
  0.437500;0.843750;,
  0.437500;0.812500;,
  0.468750;0.562500;,
  0.468750;0.625000;,
  0.437500;0.625000;,
  0.437500;0.562500;,
  0.468750;0.406250;,
  0.468750;0.437500;,
  0.437500;0.437500;,
  0.437500;0.406250;,
  0.468750;0.125000;,
  0.468750;0.187500;,
  0.437500;0.187500;,
  0.437500;0.125000;,
  0.468750;0.312500;,
  0.468750;0.343750;,
  0.437500;0.343750;,
  0.437500;0.312500;,
  0.593750;0.312500;,
  0.593750;0.343750;,
  0.562500;0.343750;,
  0.562500;0.312500;,
  0.718750;0.125000;,
  0.718750;0.187500;,
  0.687500;0.187500;,
  0.687500;0.125000;,
  0.593750;0.906250;,
  0.593750;0.937500;,
  0.562500;0.937500;,
  0.562500;0.906250;,
  0.468750;0.906250;,
  0.468750;0.937500;,
  0.437500;0.937500;,
  0.437500;0.906250;,
  0.312500;0.187500;,
  0.281250;0.187500;,
  0.281250;0.125000;,
  0.312500;0.125000;,
  0.406250;0.937500;,
  0.406250;0.906250;,
  0.406250;0.843750;,
  0.406250;0.812500;,
  0.406250;0.625000;,
  0.406250;0.562500;,
  0.406250;0.437500;,
  0.406250;0.406250;,
  0.406250;0.343750;,
  0.406250;0.312500;,
  0.406250;0.187500;,
  0.406250;0.125000;,
  0.531250;0.937500;,
  0.531250;0.906250;,
  0.531250;0.843750;,
  0.531250;0.812500;,
  0.531250;0.625000;,
  0.531250;0.562500;,
  0.531250;0.437500;,
  0.531250;0.406250;,
  0.531250;0.343750;,
  0.531250;0.312500;,
  0.531250;0.187500;,
  0.531250;0.125000;,
  0.406250;0.281250;,
  0.437500;0.281250;,
  0.468750;0.281250;,
  0.531250;0.281250;,
  0.562500;0.281250;,
  0.593750;0.281250;,
  0.656250;0.187500;,
  0.656250;0.125000;,
  0.593750;0.968750;,
  0.562500;0.968750;,
  0.531250;0.968750;,
  0.468750;0.968750;,
  0.437500;0.968750;,
  0.406250;0.968750;,
  0.343750;0.125000;,
  0.343750;0.187500;,
  0.406250;0.781250;,
  0.437500;0.781250;,
  0.468750;0.781250;,
  0.531250;0.781250;,
  0.562500;0.781250;,
  0.593750;0.781250;,
  0.843750;0.125000;,
  0.843750;0.187500;,
  0.593750;0.468750;,
  0.562500;0.468750;,
  0.531250;0.468750;,
  0.468750;0.468750;,
  0.437500;0.468750;,
  0.406250;0.468750;,
  0.156250;0.187500;,
  0.156250;0.125000;,
  0.406250;0.062500;,
  0.437500;0.062500;,
  0.468750;0.062500;,
  0.531250;0.062500;,
  0.562500;0.062500;,
  0.593750;0.062500;,
  0.656250;0.062500;,
  0.687500;0.062500;,
  0.718750;0.062500;,
  0.781250;0.062500;,
  0.812500;0.062500;,
  0.843750;0.062500;,
  0.593750;0.687500;,
  0.562500;0.687500;,
  0.531250;0.687500;,
  0.468750;0.687500;,
  0.437500;0.687500;,
  0.406250;0.687500;,
  0.156250;0.062500;,
  0.187500;0.062500;,
  0.218750;0.062500;,
  0.281250;0.062500;,
  0.312500;0.062500;,
  0.343750;0.062500;,
  0.406250;0.500000;,
  0.437500;0.500000;,
  0.468750;0.500000;,
  0.531250;0.500000;,
  0.562500;0.500000;,
  0.593750;0.500000;,
  0.812500;0.250000;,
  0.843750;0.250000;,
  0.781250;0.250000;,
  0.687500;0.250000;,
  0.718750;0.250000;,
  0.656250;0.250000;,
  0.562500;0.250000;,
  0.593750;0.250000;,
  0.531250;0.250000;,
  0.437500;0.250000;,
  0.468750;0.250000;,
  0.406250;0.250000;,
  0.312500;0.250000;,
  0.343750;0.250000;,
  0.281250;0.250000;,
  0.187500;0.250000;,
  0.218750;0.250000;,
  0.156250;0.250000;,
  0.406250;0.000000;,
  0.437500;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.562500;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.687500;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.812500;0.000000;,
  0.843750;0.000000;,
  0.562500;0.750000;,
  0.593750;0.750000;,
  0.531250;0.750000;,
  0.437500;0.750000;,
  0.468750;0.750000;,
  0.406250;0.750000;,
  0.156250;0.000000;,
  0.187500;0.000000;,
  0.218750;0.000000;,
  0.281250;0.000000;,
  0.312500;0.000000;,
  0.343750;0.000000;,
  0.468750;0.359375;,
  0.437500;0.359375;,
  0.406250;0.359375;,
  0.265625;0.250000;,
  0.265625;0.187500;,
  0.265625;0.125000;,
  0.265625;0.062500;,
  0.265625;0.000000;,
  0.406250;0.890625;,
  0.437500;0.890625;,
  0.468750;0.890625;,
  0.531250;0.890625;,
  0.562500;0.890625;,
  0.593750;0.890625;,
  0.734375;0.000000;,
  0.734375;0.062500;,
  0.734375;0.125000;,
  0.734375;0.187500;,
  0.734375;0.250000;,
  0.593750;0.359375;,
  0.562500;0.359375;,
  0.531250;0.359375;,
  0.406250;0.390625;,
  0.437500;0.390625;,
  0.468750;0.390625;,
  0.531250;0.390625;,
  0.562500;0.390625;,
  0.593750;0.390625;,
  0.765625;0.250000;,
  0.765625;0.187500;,
  0.765625;0.125000;,
  0.765625;0.062500;,
  0.765625;0.000000;,
  0.593750;0.859375;,
  0.562500;0.859375;,
  0.531250;0.859375;,
  0.468750;0.859375;,
  0.437500;0.859375;,
  0.406250;0.859375;,
  0.234375;0.000000;,
  0.234375;0.062500;,
  0.234375;0.125000;,
  0.234375;0.187500;,
  0.234375;0.250000;,
  0.500000;0.968750;,
  0.500000;0.937500;,
  0.500000;0.906250;,
  0.500000;0.890625;,
  0.500000;0.843750;,
  0.500000;0.859375;,
  0.500000;0.812500;,
  0.500000;0.781250;,
  0.500000;0.750000;,
  0.500000;0.687500;,
  0.500000;0.625000;,
  0.500000;0.562500;,
  0.500000;0.500000;,
  0.500000;0.468750;,
  0.500000;0.437500;,
  0.500000;0.406250;,
  0.500000;0.390625;,
  0.500000;0.343750;,
  0.500000;0.359375;,
  0.500000;0.312500;,
  0.500000;0.281250;,
  0.500000;0.250000;,
  0.500000;0.187500;,
  0.500000;0.125000;,
  0.500000;0.062500;,
  0.500000;0.000000;,
  0.625000;0.187500;,
  0.625000;0.250000;,
  0.625000;0.125000;,
  0.625000;0.062500;,
  0.625000;0.000000;,
  0.562500;1.000000;,
  0.593750;1.000000;,
  0.531250;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.468750;1.000000;,
  0.406250;1.000000;,
  0.375000;0.062500;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.375000;0.187500;,
  0.375000;0.250000;,
  0.875000;0.062500;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.187500;,
  0.875000;0.250000;,
  0.125000;0.187500;,
  0.125000;0.250000;,
  0.125000;0.125000;,
  0.125000;0.062500;,
  0.125000;0.000000;,
  0.625000;0.906250;,
  0.625000;0.890625;,
  0.625000;0.937500;,
  0.625000;0.968750;,
  0.625000;1.000000;,
  0.625000;0.281250;,
  0.625000;0.312500;,
  0.625000;0.343750;,
  0.625000;0.359375;,
  0.625000;0.406250;,
  0.625000;0.390625;,
  0.625000;0.437500;,
  0.625000;0.468750;,
  0.625000;0.500000;,
  0.625000;0.562500;,
  0.625000;0.625000;,
  0.625000;0.687500;,
  0.625000;0.750000;,
  0.625000;0.781250;,
  0.625000;0.812500;,
  0.625000;0.843750;,
  0.625000;0.859375;,
  0.437500;0.375000;,
  0.468750;0.375000;,
  0.406250;0.375000;,
  0.250000;0.250000;,
  0.250000;0.187500;,
  0.250000;0.125000;,
  0.250000;0.062500;,
  0.250000;0.000000;,
  0.406250;0.875000;,
  0.437500;0.875000;,
  0.468750;0.875000;,
  0.531250;0.875000;,
  0.500000;0.875000;,
  0.562500;0.875000;,
  0.593750;0.875000;,
  0.625000;0.875000;,
  0.750000;0.062500;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.750000;0.187500;,
  0.750000;0.250000;,
  0.625000;0.375000;,
  0.593750;0.375000;,
  0.562500;0.375000;,
  0.531250;0.375000;,
  0.500000;0.375000;,
  0.375000;0.968750;,
  0.375000;1.000000;,
  0.375000;0.937500;,
  0.375000;0.906250;,
  0.375000;0.890625;,
  0.375000;0.875000;,
  0.375000;0.859375;,
  0.375000;0.843750;,
  0.375000;0.812500;,
  0.375000;0.781250;,
  0.375000;0.750000;,
  0.375000;0.687500;,
  0.375000;0.625000;,
  0.375000;0.562500;,
  0.375000;0.500000;,
  0.375000;0.468750;,
  0.375000;0.437500;,
  0.375000;0.406250;,
  0.375000;0.390625;,
  0.375000;0.375000;,
  0.375000;0.359375;,
  0.375000;0.343750;,
  0.375000;0.312500;,
  0.375000;0.281250;;
 }
}
