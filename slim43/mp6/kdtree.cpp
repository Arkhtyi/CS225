/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
       
    if(second[curDim] < first[curDim])
    	return false;
    else
    	return true;
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
     double current = 0;
    
    for(int i = 0; i < Dim; i++){
    
    	current = current + ((target[i] - currentBest[i])*(target[i] - currentBest[i]));
    
    }
    
    
    
    double potentialdis = 0;
     
    for(int j = 0; j < Dim; j++){
    
    	potentialdis = potentialdis + ((target[j] - potential[j])*(target[j] - potential[j]));
    
    }
    
     
    if(potentialdis < current)	
    	return true;
    else 
    	return false;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    int pivot = (0+newPoints.size())/2;
     
    quickselect(points, 0, newPoints.size(), pivot, 0);
     
}

template<int Dim>
int KDTree<Dim>::partition(vector < Point<Dim> > & newPoints, int start, int end, int pivotIndex, int dim){
	
	int pivotValue = newPoints[pivotIndex][dim];
	std::swap(newPoints[pivotIndex], newPoints[end]);
	int storeIndex = start;
	for(int i = 0; start < end-1; i++){
		if(newPoints[i][dim] < pivotValue)
			std::swap(newPoints[storeIndex],newPoints[i]);
		storeIndex++;
	}
	std::swap(newPoints[end], newPoints[storeIndex]);
	return storeIndex;
}
template<int Dim>
void KDTree<Dim>::quickselect( vector < Point<Dim> > & newPoints, int start, int end, int pivotIndex, int dim){
	if(start >= end)
		return;
	int	pivot = partition(newPoints,start,end,pivotIndex,dim);
	if(pivotIndex < pivot - start + 1)
		quickselect(newPoints, start, pivot, pivotIndex, (dim+1)%Dim);
	else if(pivotIndex > pivot - start + 1)
		quickselect(newPoints, pivot+1, end, pivotIndex-pivot, (dim+1)%Dim);
	

}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
   return Point<Dim>();
}
