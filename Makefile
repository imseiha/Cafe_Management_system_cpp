CXX = g++
CXXFLAGS = -std=c++17
TARGET = build\cafe_system.exe

INCLUDES = -Imenu_management/include \
           -Istaff_management/include \
           -Isale_management/include \
           -Ifinancial_management/include

SRCS = main.cpp \
       $(wildcard menu_management/src/*.cpp) \
       $(wildcard staff_management/src/*.cpp) \
       $(wildcard sale_management/src/*.cpp) \
       $(wildcard financial_management/src/*.cpp)

$(TARGET): $(SRCS)
	if not exist build mkdir build
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	$(TARGET)

clean:
	if exist $(TARGET) del /Q $(TARGET)

.PHONY: run clean
