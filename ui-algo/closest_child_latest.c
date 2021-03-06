int KES_UserInterface::findClosestChild(KES_KeypadKey key, HMIScreen* screen)
{
	HMIScreen* topScreen = getTopScreen();
	int dist[MAX_COMPONENTS] = {0};
	int candidateArray1[MAX_CLOSEST_ITEMS] = {0};
	int candidateArray2[MAX_CLOSEST_ITEMS] = {0};
	int leastDist = 200;
	Box box1, box2;
	int i, j, k, currCompIdx;
	i = j = k = currCompIdx = 0;
	int selectedCandidateIndex = 0;
	int newX, newY, leastX, leastY, numCandidates, newDist;
	newX = newY = leastX = leastY = numCandidates = newDist = 0;
	int minX, minY;
	minX = minY = 0;

	//std::cout << "component stack ---------------------" << std::endl;
	//topScreen->dump_stack();
	//std::cout << "component stack ---------------------" << std::endl;
	//printf ("\n\n");

	/////////////////////////////////////////////////////////////////////////
	// get index of current focused component
	//
	// part 1:
	// foreach component in components array
	//    calculate distance between current, component --> distance array
	// tag component with least non-zero distance.
	//

	currCompIdx = topScreen->getComponentInFocus();
	if(currCompIdx < 0) {
		printf("Component in Focus is None.");
		return -1;
	}
	//std::cout << "1. current component in focus = [" << currCompIdx << "], ";
	ComponentBase *currentFComponent = topScreen->getComponentAtIndex(currCompIdx);
	box1 = currentFComponent->getBindingBox();
    currentFComponent->dump_component();
	minX = ((topScreen->getComponentAtIndex(currCompIdx))->getBindingBox()).x;
	minY = ((topScreen->getComponentAtIndex(currCompIdx))->getBindingBox()).y;

	for (i = 0; i < topScreen->getComponentStackIndex(); i++)
	{
		if (currCompIdx == i)
		{
			std::cout << "skipping self " << i << std::endl;
			dist[i] = 0;
		}
		else
		{
			dist[i] = calculateDistance(currentFComponent, topScreen->getComponentAtIndex(i));
			if ( (dist[i] > 0) && (dist[i] < leastDist) )
				leastDist = dist[i];
		}
	}
	//std::cout << "dist array:" << std::endl;
	//for (int xx = 0; xx < topScreen->getComponentStackIndex(); xx++)
	//	std::cout << "dist[" << xx << "] = " << dist[xx] << std::endl;
	//cout << endl;

	/////////////////////////////////////////////////////////////////////////
	// part 2:
	// foreach component in components array
	//     find component with select x/y criteria --> component-array2
	//

	switch (key)
	{
		case KES_CURSOR_UP:
			// x == x-curr, y < y-curr
#if 0
			j = 0;
			for (i = 0; i < topScreen->getComponentStackIndex(); i++)
			{
				if (i != currCompIdx)
				{
					box2 = (topScreen->getComponentAtIndex(i))->getBindingBox();
					//if ( ((box2.x == box1.x) && (box2.y < box1.y)) && (dist[i] == leastDist) )
					if ( (box2.y < box1.y) && (box2.x <= box1.x) )
						candidateArray1[j++] = i;
				}
			}
#endif

			// step 1: select all elements lying to top side.
			j = 0;
			for (i = 0; i < topScreen->getComponentStackIndex(); i++)
			{
				if (i != currCompIdx)
				{
					box2 = (topScreen->getComponentAtIndex(i))->getBindingBox();
					//if ( ((box2.x == box1.x) && (box2.y < box1.y)) && (dist[i] == leastDist) )
					if (box2.y < box1.y)
						candidateArray1[j++] = i;  // store only index
				}
			}
			numCandidates = j;
			//cout << "step 1: all top candidates" << endl;
			//for (i = 0; i < numCandidates; i++)
			//{
			//	cout << "[" << i << "] i.e. " << candidateArray1[i] << ": ";
			//	(topScreen->getComponentAtIndex(candidateArray1[i]))->dump_component();
			//}
			//cout << endl;

			// step 2:
			// from all "top" candidates, select the ones which are immediately at top.
			newY = 0;
			k = 0;
			leastY = ((topScreen->getComponentAtIndex(candidateArray1[0]))->getBindingBox()).y;
			for (int i = 0; i < numCandidates; i++)
			{
				newY = ((topScreen->getComponentAtIndex(candidateArray1[i]))->getBindingBox()).y;
				if (newY >= leastY)
					candidateArray2[k++] = candidateArray1[i];
			}
			numCandidates = k;
			//cout << "step 2: all immediate top candidates" << endl;
			//for (i = 0; i < k; i++)
			//{
			//	cout << "[" << i << "] i.e. " << candidateArray2[i] << ": ";
			//	(topScreen->getComponentAtIndex(candidateArray2[i]))->dump_component();
			//}
			//cout << endl;

			// step 3:
			// from all immediate "top" candidates, select the candidate with least X.
			newX = 0;
			leastX = ((topScreen->getComponentAtIndex(candidateArray2[0]))->getBindingBox()).x;
			leastDist = dist [candidateArray2[0]];
			for (int i = 0; i < numCandidates; i++)
			{
				newX = ((topScreen->getComponentAtIndex(candidateArray2[i]))->getBindingBox()).x;
				newDist = dist[candidateArray2[i]];
				//if (newX < leastX)
				if (newDist <= leastDist)
				{
					selectedCandidateIndex = candidateArray2[i];
					leastDist = newDist;
				}
			}
			//cout << "step 3: search exact candidate" << endl;
			//cout << "[" << selectedCandidateIndex << "] i.e. " << selectedCandidateIndex << ": ";
			//(topScreen->getComponentAtIndex(selectedCandidateIndex))->dump_component();

			break;
		case KES_CURSOR_DOWN:
			// x == x-curr, y > y-curr
#if 0
			j = 0;
			for (i = 0; i < topScreen->getComponentStackIndex(); i++)
			{
				if (i != currCompIdx)
				{
					box2 = (topScreen->getComponentAtIndex(i))->getBindingBox();
					//if ( ((box2.x == box1.x) && (box2.y > box1.y)) && (dist[i] == leastDist) )
					if ( (box2.y > box1.y) && (box2.x >= box1.x) )
						candidateArray1[j++] = i;
				}
			}
#endif

			// step 1: select all elements lying to bottom side.
			j = 0;
			for (i = 0; i < topScreen->getComponentStackIndex(); i++)
			{
				if (i != currCompIdx)
				{
					box2 = (topScreen->getComponentAtIndex(i))->getBindingBox();
					//if ( ((box2.x == box1.x) && (box2.y > box1.y)) && (dist[i] == leastDist) )
					if (box2.y > box1.y)
						candidateArray1[j++] = i;  // store only index
				}
			}
			numCandidates = j;
			//cout << "step 1: all bottom candidates" << endl;
			//for (i = 0; i < numCandidates; i++)
			//{
			//	cout << "[" << i << "] i.e. " << candidateArray1[i] << ": ";
			//	(topScreen->getComponentAtIndex(candidateArray1[i]))->dump_component();
			//}
			//cout << endl;

			// step 2:
			// from all "bottom" candidates, select the ones which are immediately at bottom.
			newY = 0;
			k = 0;
			leastY = ((topScreen->getComponentAtIndex(candidateArray1[0]))->getBindingBox()).y;
			for (int i = 0; i < numCandidates; i++)
			{
				newX = ((topScreen->getComponentAtIndex(candidateArray1[i]))->getBindingBox()).x;
				newY = ((topScreen->getComponentAtIndex(candidateArray1[i]))->getBindingBox()).y;
				if ((newY <= leastY) || (minX == newX))
					candidateArray2[k++] = candidateArray1[i];
			}
			numCandidates = k;
			//cout << "step 2: all immediate bottom candidates" << endl;
			//for (i = 0; i < k; i++)
			//{
			//	cout << "[" << i << "] i.e. " << candidateArray2[i] << ": ";
			//	(topScreen->getComponentAtIndex(candidateArray2[i]))->dump_component();
			//}
			//cout << endl;

			// step 3:
			// from all immediate "bottom" candidates, select the candidate with least X.
			newX = 0;
			leastX = ((topScreen->getComponentAtIndex(candidateArray2[0]))->getBindingBox()).x;
			leastDist = dist [candidateArray2[0]];
			for (int i = 0; i < numCandidates; i++)
			{
				newX = ((topScreen->getComponentAtIndex(candidateArray2[i]))->getBindingBox()).x;
				newDist = dist [candidateArray2[i]];
				//cout << "3. [" << candidateArray2[i] << "]: ";
				//cout << " L: " << leastDist << " N: " << newDist;
				//cout << " Lx: " << leastX << " Nx: " << newX << endl;
				//if (newX < leastX)
				if (newDist <= leastDist)
				{
					//xif (newDist == leastDist)
					//x{
						//xif (newX < leastX)
						//x{
							//xselectedCandidateIndex = candidateArray2[i];
							leastX = newX;
						//x}
					//x}
					//xelse
					//x{
					    selectedCandidateIndex = candidateArray2[i];
					    leastDist = newDist;
					//x}
				}
			}
			//cout << "step 3: search exact candidate" << endl;
			//cout << "[" << selectedCandidateIndex << "] i.e. " << selectedCandidateIndex << ": ";
			//(topScreen->getComponentAtIndex(selectedCandidateIndex))->dump_component();

			break;
		case KES_CURSOR_LEFT:
			// x < x-curr
			// step 1: select all elements lying to left side.
			j = 0;
			for (i = 0; i < topScreen->getComponentStackIndex(); i++)
			{
				if (i != currCompIdx)
				{
					box2 = (topScreen->getComponentAtIndex(i))->getBindingBox();
					if (box2.x < box1.x)
						candidateArray1[j++] = i;  // store only index
				}
			}
			numCandidates = j;
			//cout << "step 1: all left candidates" << endl;
			//for (i = 0; i < numCandidates; i++)
			//{
			//	cout << "[" << i << "] i.e. " << candidateArray1[i] << ": ";
			//	(topScreen->getComponentAtIndex(candidateArray1[i]))->dump_component();
			//}
			//cout << endl;

			// step 2:
			// from all "left" candidates, select the ones which are immediately at left.
			newX = 0;
			k = 0;
			leastX = ((topScreen->getComponentAtIndex(candidateArray1[0]))->getBindingBox()).x;
			for (int i = 0; i < numCandidates; i++)
			{
				newX = ((topScreen->getComponentAtIndex(candidateArray1[i]))->getBindingBox()).x;
				if (newX >= leastX)
					candidateArray2[k++] = candidateArray1[i];
			}
			numCandidates = k;
			//cout << "step 2: all immediate left candidates" << endl;
			//for (i = 0; i < k; i++)
			//{
			//	cout << "[" << i << "] i.e. " << candidateArray2[i] << ": ";
			//	(topScreen->getComponentAtIndex(candidateArray2[i]))->dump_component();
			//}
			//cout << endl;

			// step 3:
			// from all immediate "left" candidates, select the candidate with least Y.
			newY = 0;
			leastY = ((topScreen->getComponentAtIndex(candidateArray2[0]))->getBindingBox()).y;
			leastDist = dist [candidateArray2[0]];
			for (int i = 0; i < numCandidates; i++)
			{
				newY = ((topScreen->getComponentAtIndex(candidateArray2[i]))->getBindingBox()).y;
				newDist = dist[candidateArray2[i]];
				if (newDist <= leastDist)
				{
					if (newDist == leastDist)
					{
						if (newY <= leastY)
						{
							selectedCandidateIndex = candidateArray2[i];
							leastY = newY;
						}
					}
					else if (newDist < leastDist)
					{
						if (newY <= minY)
						    selectedCandidateIndex = candidateArray2[i];
					}
				    else
					{
					    selectedCandidateIndex = candidateArray2[i];
					    leastDist = newDist;
					}
				}
			}
			//cout << "step 3: search exact candidate" << endl;
			//cout << "[" << selectedCandidateIndex << "] i.e. " << selectedCandidateIndex << ": ";
			//(topScreen->getComponentAtIndex(selectedCandidateIndex))->dump_component();

			break;
		case KES_CURSOR_RIGHT:
			// x > x-curr
			// step 1: select all elements lying to right side.
			j = 0;
			for (i = 0; i < topScreen->getComponentStackIndex(); i++)
			{
				if (i != currCompIdx)
				{
					box2 = (topScreen->getComponentAtIndex(i))->getBindingBox();
					//if ( ((box2.x > box1.x) && (box2.y == box1.y)) && (dist[i] == leastDist) )
					if ( (box2.x > box1.x) )
						candidateArray1[j++] = i;  // store only index
				}
			}
			numCandidates = j;
			//cout << "step 1: all right candidates" << endl;
			//for (i = 0; i < numCandidates; i++)
			//{
			//	cout << "[" << i << "] i.e. " << candidateArray1[i] << ": ";
			//	(topScreen->getComponentAtIndex(candidateArray1[i]))->dump_component();
			//}
			//cout << endl;

			// step 2:
			// from all "right" candidates, select the ones which are immediately at right.
			newX = 0;
			k = 0;
			leastX = ((topScreen->getComponentAtIndex(candidateArray1[0]))->getBindingBox()).x;
			for (int i = 0; i < numCandidates; i++)
			{
				newX = ((topScreen->getComponentAtIndex(candidateArray1[i]))->getBindingBox()).x;
				newY = ((topScreen->getComponentAtIndex(candidateArray1[i]))->getBindingBox()).y;
				if ((newX <= leastX) || (minY == newY))
					candidateArray2[k++] = candidateArray1[i];
			}
			numCandidates = k;
			//cout << "step 2: all immediate right candidates" << endl;
			//for (i = 0; i < k; i++)
			//{
			//	cout << "[" << i << "] i.e. " << candidateArray2[i] << ": ";
			//	(topScreen->getComponentAtIndex(candidateArray2[i]))->dump_component();
			//}
			//cout << endl;

			// step 3:
			// from all immediate "right" candidates, select the candidate with least Y.
			newY = 0;
			leastY = ((topScreen->getComponentAtIndex(candidateArray2[0]))->getBindingBox()).y;
			leastDist = dist [candidateArray2[0]];
			for (int i = 0; i < numCandidates; i++)
			{
				newY = ((topScreen->getComponentAtIndex(candidateArray2[i]))->getBindingBox()).y;
				newDist = dist[candidateArray2[i]];
				//cout << "[" << candidateArray2[i] << "]: Ld = " << leastDist << ", Nd = " << newDist;
				//cout << " Ly = " << leastY << " newY = " << newY;
				//if ( (newY < leastY) && (newDist < leastDist) )
				if (newDist <= leastDist)
				{
					if (newDist == leastDist)
					{
						if (newY <= leastY)
						{
						    selectedCandidateIndex = candidateArray2[i];
						    leastY = newY;
						}
					}
					else if (newDist < leastDist)
					{
						if (newY <= minY)
							selectedCandidateIndex = candidateArray2[i];
					}
					else
					{
						selectedCandidateIndex = candidateArray2[i];
						leastDist = newDist;
					}
				}
				//leastY = newY;
				//cout << " selected: " << selectedCandidateIndex << endl;
			}
			//cout << "step 3: search exact candidate" << endl;
			//cout << "[" << selectedCandidateIndex << "] i.e. " << selectedCandidateIndex << ": ";
			//(topScreen->getComponentAtIndex(selectedCandidateIndex))->dump_component();

			break;
		default:
			break;
	}

	//std::cout << "selected closest item = " << candidateArray2[selectedCandidateIndex] << " ";
	//(topScreen->getComponentAtIndex(candidateArray2[selectedCandidateIndex]))->dump_component();
	//printf ("--------------\n\n");

#if 0
	//int maxElib = j;
	//std::cout << "2. built array of eligible candidates [" << maxElib << "]:" << std::endl;
	//for (int ii = 0; ii < maxElib; ii++)
	//{
		//std::cout << "candid[" << ii << "] = " << candidateArray1[ii] << " D = " << dist[ candidateArray1[ii] ] << " ";
		//(topScreen->getComponentAtIndex(candidateArray1[ii]))->dump_component();
	//}

	/////////////////////////////////////////////////////////////////////////
	// part 3
	// select tagged component from part 1 in component-array2
	// return component
	// TODO: add check for more than 1 candidates.

	int ld2 = dist[ candidateArray1[0] ];
	int idx2 = 1;
	for (int i = 1; i < maxElib; i++)
	{
		//if (candidateArray1[i] == closestItem)
			//break;
		if (ld2 > dist[ candidateArray1[i] ])
			idx2 = i;
	}
#endif

	return (selectedCandidateIndex);
}
