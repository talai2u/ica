##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ica-master
ConfigurationName      :=Debug
WorkspacePath          :=G:/Projects/TALAI/ica-master
ProjectPath            :=G:/Projects/TALAI/ica-master
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=h.elhaidaoui
Date                   :=27/12/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="ica-master.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/myAlgorithm.cpp$(ObjectSuffix) $(IntermediateDirectory)/Problem.cpp$(ObjectSuffix) $(IntermediateDirectory)/SetUpParams.cpp$(ObjectSuffix) $(IntermediateDirectory)/Solution.cpp$(ObjectSuffix) $(IntermediateDirectory)/Utils.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/myAlgorithm.cpp$(ObjectSuffix): myAlgorithm.cpp $(IntermediateDirectory)/myAlgorithm.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Projects/TALAI/ica-master/myAlgorithm.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/myAlgorithm.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/myAlgorithm.cpp$(DependSuffix): myAlgorithm.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/myAlgorithm.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/myAlgorithm.cpp$(DependSuffix) -MM myAlgorithm.cpp

$(IntermediateDirectory)/myAlgorithm.cpp$(PreprocessSuffix): myAlgorithm.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/myAlgorithm.cpp$(PreprocessSuffix) myAlgorithm.cpp

$(IntermediateDirectory)/Problem.cpp$(ObjectSuffix): Problem.cpp $(IntermediateDirectory)/Problem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Projects/TALAI/ica-master/Problem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Problem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Problem.cpp$(DependSuffix): Problem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Problem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Problem.cpp$(DependSuffix) -MM Problem.cpp

$(IntermediateDirectory)/Problem.cpp$(PreprocessSuffix): Problem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Problem.cpp$(PreprocessSuffix) Problem.cpp

$(IntermediateDirectory)/SetUpParams.cpp$(ObjectSuffix): SetUpParams.cpp $(IntermediateDirectory)/SetUpParams.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Projects/TALAI/ica-master/SetUpParams.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SetUpParams.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SetUpParams.cpp$(DependSuffix): SetUpParams.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SetUpParams.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SetUpParams.cpp$(DependSuffix) -MM SetUpParams.cpp

$(IntermediateDirectory)/SetUpParams.cpp$(PreprocessSuffix): SetUpParams.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SetUpParams.cpp$(PreprocessSuffix) SetUpParams.cpp

$(IntermediateDirectory)/Solution.cpp$(ObjectSuffix): Solution.cpp $(IntermediateDirectory)/Solution.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Projects/TALAI/ica-master/Solution.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Solution.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Solution.cpp$(DependSuffix): Solution.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Solution.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Solution.cpp$(DependSuffix) -MM Solution.cpp

$(IntermediateDirectory)/Solution.cpp$(PreprocessSuffix): Solution.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Solution.cpp$(PreprocessSuffix) Solution.cpp

$(IntermediateDirectory)/Utils.cpp$(ObjectSuffix): Utils.cpp $(IntermediateDirectory)/Utils.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Projects/TALAI/ica-master/Utils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Utils.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Utils.cpp$(DependSuffix): Utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Utils.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Utils.cpp$(DependSuffix) -MM Utils.cpp

$(IntermediateDirectory)/Utils.cpp$(PreprocessSuffix): Utils.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Utils.cpp$(PreprocessSuffix) Utils.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


