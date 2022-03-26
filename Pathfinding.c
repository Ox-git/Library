#include "MainInclude.h"



BKPathfinder AIPathfinder[4];




//Before running the function below, ensure that you've set the `Target` value 
//of the BKPathfinder to the float-position of the position you wish to drive towards. 

void UpdateBKPath(BKPathfinder* Pathfinder, Marker *PathArray[], short* MarkerCounts, short PathCount, short PlayerID)
{
     float CheckDistance;
     Pathfinder->Distance = 999999999; // Set an impossible value to ensure the first return is true. 

     Pathfinder->LastPath = Pathfinder->TargetPath; //Set the last path as we get ready to update.
     for (int ThisPath = 0; ThisPath < PathCount; ThisPath++)
     {
          //Test first marker to see if in range.
          objectPosition[0] = (float)PathArray[ThisPath][0].Position[0];
          objectPosition[0] = (float)PathArray[ThisPath][0].Position[0];
          objectPosition[0] = (float)PathArray[ThisPath][0].Position[0];

          if (TestCollideSphere(GlobalPlayer[PlayerID].position, 125, objectPosition, 5))  //check if the first marker is within 125 units of the player
          {
               //First Marker has hit true, check distance of last marker
               CheckDistance = 
               (
                    ((float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[0] - Pathfinder->Target[0]) * ((float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[0] - Pathfinder->Target[0]) +
                    ((float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[1] - Pathfinder->Target[1]) * ((float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[1] - Pathfinder->Target[1]) + 
                    ((float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[2] - Pathfinder->Target[2]) * ((float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[2] - Pathfinder->Target[2])
               );  //(A^2 + B^2 + C^2) = d
               if (CheckDistance < Pathfinder->Distance)  //compare distance, if less than the current update
               {
                    Pathfinder->Distance = CheckDistance;
                    Pathfinder->TargetPath = ThisPath;
               }
          }
          else
          {
               //Test last marker to see if in range.
               objectPosition[0] = (float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[0];
               objectPosition[1] = (float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[1];
               objectPosition[2] = (float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[2];

               if (TestCollideSphere(GlobalPlayer[PlayerID].position, 125, objectPosition, 5))  //check if the last marker is within 125 units of the player
               {
                    //First Marker has hit true, check distance of last marker
                    CheckDistance = 
                    (
                         ((float)PathArray[ThisPath][0].Position[0] - Pathfinder->Target[0]) * ((float)PathArray[ThisPath][0].Position[0] - Pathfinder->Target[0]) +
                         ((float)PathArray[ThisPath][0].Position[1] - Pathfinder->Target[1]) * ((float)PathArray[ThisPath][0].Position[1] - Pathfinder->Target[1]) + 
                         ((float)PathArray[ThisPath][0].Position[2] - Pathfinder->Target[2]) * ((float)PathArray[ThisPath][0].Position[2] - Pathfinder->Target[2])
                    );  //(A^2 + B^2 + C^2) = d
                    if (CheckDistance < Pathfinder->Distance)  //compare distance, if less than the current update
                    {
                         Pathfinder->Distance = CheckDistance;
                         Pathfinder->TargetPath = ThisPath;
                    }
               }
          }
     }
}