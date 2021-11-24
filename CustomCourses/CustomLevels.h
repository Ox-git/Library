#ifndef CustomLebelsH
#define CustomLevelsH
#include "../MainInclude.h"
extern void stockASM();
extern void overkartASM();
extern void runTextureScroll();
extern void runWaterVertex();
extern void runDisplayScreen();
extern void loadTextureScrollTranslucent();
extern void copyCourseTable();
extern void hsTableSet();
extern void stockTableSet();
extern void setSong();
extern void setTempo();
extern void setPath();
extern void setEcho();
extern void setSky();
extern void setWater();
extern void loadHeaderOffsets();
extern void LoadCustomHeader(int inputID);
extern void SetCustomData();
extern void loadMinimap();
extern void loadOKObjects();
extern void setOKObjects();
extern void setLabel();
extern void setBanners();
extern void setPreviews();
extern void swapHS();
extern void previewRefresh();
extern void SetCourseNames(bool custom);
extern void initFireParticles(long PathOffset);
extern void DisplayFireParticleSub(int num,uchar color,void* Camera);
extern void SetWeatherType(int WeatherType);
extern void SetCloudType(char CloudType);
extern void SetWeather3D(bool Weather3DEnable);
extern void Snow3DCameralook(int num, void* Camera);
extern void EventDisplay(int player);
extern void EventDisplay_After(int player);
extern void CommonGameEventChart();
extern void EmptyActionData(); 
#endif