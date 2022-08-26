#include "../MainInclude.h"




BKPathfinder AIPathfinder[4];




//Before running the function below, ensure that you've set the `Target` value 
//of the BKPathfinder to the float-position of the position you wish to drive towards. 





bool PathfinderComplete(BKPathfinder *Pathfinder, short *PathLengths, short *RampLengths, short *DropLengths)
{
    switch (Pathfinder->PathType)
    {
        case FLATPATH:
        {            
            return 
            (
                (Pathfinder->ProgressTimer >= 60)
                || (Pathfinder->TargetPath == -1) 
                || (Pathfinder->NearestMarker==0 && Pathfinder->Direction==-1)  
                || (Pathfinder->NearestMarker==PathLengths[Pathfinder->TargetPath] && Pathfinder->Direction==1) 
                || (Pathfinder->NearestMarker < 0) 
                || (Pathfinder->NearestMarker > PathLengths[Pathfinder->TargetPath])
            ); //If bot reaches end of path
            break;
        }

        case RAMPPATH:
        {            
            return 
            (
                (Pathfinder->ProgressTimer >= 60)
                || (Pathfinder->TargetPath == -1) 
                || (Pathfinder->NearestMarker==0 && Pathfinder->Direction==-1)  
                || (Pathfinder->NearestMarker==RampLengths[Pathfinder->TargetPath] && Pathfinder->Direction==1) 
                || (Pathfinder->NearestMarker < 0) 
                || (Pathfinder->NearestMarker > RampLengths[Pathfinder->TargetPath])
            ); //If bot reaches end of path
            break;
        }

        case DROPPATH:
        {            
            return 
            (
                (Pathfinder->ProgressTimer >= 60)
                || (Pathfinder->TargetPath == -1) 
                || (Pathfinder->NearestMarker==0 && Pathfinder->Direction==-1)  
                || (Pathfinder->NearestMarker==DropLengths[Pathfinder->TargetPath] && Pathfinder->Direction==1) 
                || (Pathfinder->NearestMarker < 0) 
                || (Pathfinder->NearestMarker > DropLengths[Pathfinder->TargetPath])
            ); //If bot reaches end of path
            break;
        }
    }
    return false;
}
int FindNearestRampNode(float CurrentPosition[], float FoundNodePosition[], float TargetY, Marker* PathArray[], short* MarkerCounts, short PathCount)
{
    float Distance = 9999999.0;
    float CheckDistance;
    float path_height_start_node, path_height_end_node;
    float height_check;
    short use_this_path= 0;
    short use_this_marker=0;
    float diff_x, diff_z;

    float PathDistanceDifference = -1;
    float TargetHeightDifference = CurrentPosition[1] - TargetY;
    TargetHeightDifference *= TargetHeightDifference; //Square to get absolute distance. 
    
    for (int ThisPath = 0; ThisPath < PathCount; ThisPath++) //Loop through each possible path and check the beginning and ending nodes and save the closest one to CurrentPosition
    {
        path_height_start_node = (float)PathArray[ThisPath][0].Position[1];
        path_height_end_node = (float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[1];

        height_check = CurrentPosition[1] - path_height_start_node;

        //Check beginning of path
        if (height_check*height_check < 400)
        {
            
            PathDistanceDifference = path_height_end_node - TargetY;
            PathDistanceDifference *= PathDistanceDifference;
            if (PathDistanceDifference < TargetHeightDifference)
            {
                diff_x = CurrentPosition[0] - (float)PathArray[ThisPath][0].Position[0];
                diff_z = CurrentPosition[2] - (float)PathArray[ThisPath][0].Position[2];
                CheckDistance = diff_x*diff_x + diff_z*diff_z;
                if (CheckDistance < Distance)
                {
                    Distance = CheckDistance;
                    use_this_path = ThisPath;
                    use_this_marker = 0;
                }
            }
        }
        //Check end of path
        height_check = CurrentPosition[1] - path_height_end_node;

        if (height_check*height_check < 400)
        {
        
            PathDistanceDifference = path_height_start_node - TargetY;
            PathDistanceDifference *= PathDistanceDifference;
            if (PathDistanceDifference < TargetHeightDifference)
            {
                diff_x = CurrentPosition[0] - (float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[0];
                diff_z = CurrentPosition[2] - (float)PathArray[ThisPath][MarkerCounts[ThisPath]].Position[2];
                CheckDistance = diff_x*diff_x + diff_z*diff_z;
                if (CheckDistance < Distance)
                {
                    Distance = CheckDistance;
                    use_this_path = ThisPath;
                    use_this_marker = MarkerCounts[ThisPath];
                }
            }
        }
    }   
    //Vector that will be returned
    FoundNodePosition[0] = (float)PathArray[use_this_path][use_this_marker].Position[0]; 
    FoundNodePosition[1] = (float)PathArray[use_this_path][use_this_marker].Position[1];
    FoundNodePosition[2] = (float)PathArray[use_this_path][use_this_marker].Position[2];

    return(use_this_path);
}



void UpdateBKPath(BKPathfinder* Pathfinder, short FirstMarkerDistance, Marker *PathArray[], short* MarkerCounts, short PathCount, short PlayerID, char TypeOfPath)
{
    //float CheckHeightStart; 
    //float CheckHeightEnd;
    float CheckDistance;
    //float diff_x, diff_y, diff_z;
    float diff_x, diff_z;
    float height_check;
    Pathfinder->Distance = 9999999.0; // Set an impossible value to ensure the first return is true. 
    if (Pathfinder->TargetPath != -1)
    {
        Pathfinder->LastPath = Pathfinder->TargetPath; //Set the last path as we get ready to update.
    }
    Pathfinder->TargetPath = -1;     
    for (int ThisPath = 0; ThisPath < PathCount; ThisPath++)
    {
        height_check = GlobalPlayer[PlayerID].position[1] - (float)PathArray[ThisPath][0].Position[1];
        if (height_check*height_check < 400) //If on same level
        {
            //Test first marker to see if in range.
            objectPosition[0] = (float)PathArray[ThisPath][0].Position[0];
            objectPosition[1] = (float)PathArray[ThisPath][0].Position[1];
            objectPosition[2] = (float)PathArray[ThisPath][0].Position[2];

            if (TestCollideSphere(GlobalPlayer[PlayerID].position, FirstMarkerDistance, objectPosition, 5)) //&& (ThisPath != Pathfinder->LastPath))  //check if the first marker is within 125 units of the player
            {
                //First Marker has hit true, check distance of last marker
                diff_x = ((float)PathArray[ThisPath][MarkerCounts[ThisPath]-1].Position[0] - Pathfinder->Target[0]);
                //diff_y = ((float)PathArray[ThisPath][MarkerCounts[ThisPath]-1].Position[1] - Pathfinder->Target[1]);
                diff_z = ((float)PathArray[ThisPath][MarkerCounts[ThisPath]-1].Position[2] - Pathfinder->Target[2]);
                CheckDistance = diff_x*diff_x + diff_z*diff_z;  //(A^2 + B^2 + C^2) = d
                // CheckDistance = diff_x*diff_x + diff_z*diff_z;


                if (CheckDistance < Pathfinder->Distance)  //compare distance, if less than the current update
                {
                    Pathfinder->Distance = CheckDistance;
                    Pathfinder->TargetPath = ThisPath;
                    // Pathfinder->Progression = MarkerCounts[ThisPath]-1;
                    // Pathfinder->Direction = -1;
                    Pathfinder->Progression = 0;
                    Pathfinder->Direction = 1;
                    Pathfinder->PathType = TypeOfPath;
                    Pathfinder->NearestMarker = 0;
                    Pathfinder->ProgressTimer = 0;
                }
            }
        }

        height_check =  GlobalPlayer[PlayerID].position[1] - (float)PathArray[ThisPath][MarkerCounts[ThisPath]-1].Position[1];
        if (height_check*height_check < 400) //If on same level
        {
            //Test last marker to see if in range.
            objectPosition[0] = (float)PathArray[ThisPath][MarkerCounts[ThisPath]-1].Position[0];
            objectPosition[1] = (float)PathArray[ThisPath][MarkerCounts[ThisPath]-1].Position[1];
            objectPosition[2] = (float)PathArray[ThisPath][MarkerCounts[ThisPath]-1].Position[2];

            if (TestCollideSphere(GlobalPlayer[PlayerID].position, FirstMarkerDistance, objectPosition, 5))// && (ThisPath != Pathfinder->LastPath))  //check if the last marker is within 125 units of the player
            {
                //First Marker has hit true, check distance of last marker
                diff_x = ((float)PathArray[ThisPath][0].Position[0] - Pathfinder->Target[0]);
                //diff_y = ((float)PathArray[ThisPath][0].Position[1] - Pathfinder->Target[1]);
                diff_z = ((float)PathArray[ThisPath][0].Position[2] - Pathfinder->Target[2]);
                CheckDistance = diff_x*diff_x + diff_z*diff_z;  //(A^2 + B^2 + C^2) = d
                // CheckDistance = diff_x*diff_x + diff_z*diff_z;  //(A^2 + B^2 + C^2) = d

                if (CheckDistance < Pathfinder->Distance)  //compare distance, if less than the current update
                {
                    Pathfinder->Distance = CheckDistance;
                    Pathfinder->TargetPath = ThisPath;
                    // Pathfinder->Progression = 0;
                    // Pathfinder->Direction = 1;
                    Pathfinder->Progression = MarkerCounts[ThisPath];
                    Pathfinder->Direction = -1;
                    Pathfinder->PathType = TypeOfPath;
                    Pathfinder->NearestMarker = MarkerCounts[ThisPath];
                    Pathfinder->ProgressTimer = 0;
                }
            }
        }
    }


    if (Pathfinder->TargetPath == -1)
    {
        //Default catch for no found paths
        Pathfinder->TargetPath = Pathfinder->LastPath;
        if (Pathfinder->Direction == 0)
        {
            Pathfinder->Progression = 0;
        }
        else
        {
            Pathfinder->Progression = MarkerCounts[Pathfinder->TargetPath];
        }
        
    }
}


    


void ResetLaneDefaultOffset(int playerID)
{
    switch (MakeRandomLimmit(3))
    {
    case 0:
        LaneData[playerID].lane_free_drive = -(g_RoadWidth[0] * 0.005f);
        break;
    case 1:
        LaneData[playerID].lane_free_drive = 0;
        break;
    case 2:
        LaneData[playerID].lane_free_drive = (g_RoadWidth[0] * 0.005f);
        break;        
    default:
        break;
    }
    LaneData[playerID].speed = 10.0f;
}

void ChooseAlternativePathRandm(int playerID, short pointCheckMin, short pointCheckMax, ushort maxPathIDs)
{
    if (g_playerPathPointTable[playerID] >= pointCheckMin && g_playerPathPointTable[playerID] <= pointCheckMax)
    {
        CurrentPathID[playerID] = MakeRandomLimmit(maxPathIDs);
        ResetLaneDefaultOffset(playerID);
    }
}

void ChangePathAndPoint(int playerID, short pointCheckMin, short pointCheckMax, ushort currentpathID, ushort newpathID)
{
    if (CurrentPathID[playerID] != currentpathID)
    {
        return;
    }
    
    if (g_playerPathPointTable[playerID] >= pointCheckMin && g_playerPathPointTable[playerID] <= pointCheckMax)
    {
        CurrentPathID[playerID] = newpathID;
        g_playerPathPointTable[playerID] = pointCheckMax;
        ResetLaneDefaultOffset(playerID);
    }
}


void MakeAlternativePath(Marker *altPath, short length, char pathID)
{

    CenterPathBP[(int)pathID] = (Marker*)altPath;
    g_courseTotalPathPoints[(int)pathID] = length;
    MaxPathPoints[(int)pathID] = length;

    for (int i = 0; i < length; i++)
    {
        CenterPathBP[(int)pathID][i].Position[0] *= g_mirrorValue;
        CenterPathBP[(int)pathID][i].Group = CenterPathBP[0][i].Group;
    }

    SideLPathBP[(int)pathID] = (Marker *)AllocateMemory(MaxPathPoints[(int)pathID]*(sizeof(Marker)));
    SideRPathBP[(int)pathID] = (Marker *)AllocateMemory(MaxPathPoints[(int)pathID]*(sizeof(Marker)));
    CurvePathDataBP[(int)pathID] = (short *)AllocateMemory(MaxPathPoints[(int)pathID]*(sizeof(short)));
    AnglePathDataBP[(int)pathID] = (short *)AllocateMemory(MaxPathPoints[(int)pathID]*(sizeof(short)));
    ShortCutPathDataBP[(int)pathID] = (short *)AllocateMemory(MaxPathPoints[(int)pathID]*(sizeof(short)));

    SidePointCalcBP((int)pathID);
    CurveDataCalcBP((int)pathID);
    AngleDataCalcBP((int)pathID);
    ShortcutDataCalcBP((int)pathID);
}