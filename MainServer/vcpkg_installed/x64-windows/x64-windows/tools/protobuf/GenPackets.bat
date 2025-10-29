@echo off
pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./Enum.proto
protoc.exe -I=./ --cpp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ ./Protocol.proto

protoc.exe -I=./ --csharp_out=./ ./Enum.proto
protoc.exe -I=./ --csharp_out=./ ./Struct.proto
protoc.exe -I=./ --csharp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --recv=REQ_ --send=RES_ --notify=NOTIFY_
IF ERRORLEVEL 1 PAUSE

XCOPY /Y Enum.pb.h "../../../../../Protocol"
XCOPY /Y Enum.pb.cc "../../../../../Protocol"
XCOPY /Y Struct.pb.h "../../../../../Protocol"
XCOPY /Y Struct.pb.cc "../../../../../Protocol"
XCOPY /Y Protocol.pb.h "../../../../../Protocol"
XCOPY /Y Protocol.pb.cc "../../../../../Protocol"
XCOPY /Y ServerPacketHandler.h "../../../../../h"

XCOPY /Y Enum.cs "C:\Users\User\Documents\GitHub\Fishing-Project_client\Assets\9. Server\Packet\Protocol"
XCOPY /Y Struct.cs "C:\Users\User\Documents\GitHub\Fishing-Project_client\Assets\9. Server\Packet\Protocol"
XCOPY /Y Protocol.cs "C:\Users\User\Documents\GitHub\Fishing-Project_client\Assets\9. Server\Packet\Protocol"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h
DEL /Q /F *.cs

PAUSE