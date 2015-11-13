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
    else if(second[curDim] == first[curDim])
    	return first < second;
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
    else if (potentialdis == current)
    		return potential < currentBest;
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
     
    buildtree(points, 0, points.size()-1, pivot, 0);
     
}

template<int Dim>
void KDTree<Dim>::buildtree(vector < Point<Dim> > & newPoints, int start, int end, int pivotIndex, int dim){
	
	if(start >= end)
		return;
	
	int pivot = quickselect(newPoints,start, end, pivotIndex, dim);
	
	buildtree(newPoints, start, pivot-1, (start+pivot-1)/2, (dim+1)%Dim);
	buildtree(newPoints, pivot+1, end, (pivot+1+end)/2, (dim+1)%Dim);
	
	

}


template<int Dim>
int KDTree<Dim>::partition(vector < Point<Dim> > & newPoints, int start, int end, int pivotIndex, int dim){
	
	std::swap(newPoints[pivotIndex], newPoints[end]);
	int storeIndex = end - 1;
	for(; start != storeIndex; ){
		if(!smallerDimVal(newPoints[start], newPoints[end], dim)){
			std::swap(newPoints[storeIndex],newPoints[start]);
			storeIndex--;
		}else{
			start++;
		}
	}
	if(smallerDimVal(newPoints[start], newPoints[end],dim)){
		std::swap(newPoints[end], newPoints[storeIndex+1]);
		return storeIndex+1;
	}else{
		std::swap(newPoints[end], newPoints[storeIndex]);
		return storeIndex;
	}
}
template<int Dim>
int KDTree<Dim>::quickselect( vector < Point<Dim> > & newPoints, int start, int end, int pivotIndex, int dim){
	if(start >= end)
		return start;
	int	pivot = partition(newPoints,start,end,start,dim);
	if(pivot > pivotIndex)
		return quickselect(newPoints, start, pivot-1, pivotIndex, dim);
	else if(pivot < pivotIndex)
		return quickselect(newPoints, pivot+1, end, pivotIndex, dim);
	else
		return pivot;

}
 
template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
     
   
  	int pivot = ((points.size()-1)/2);
	return FNNHelper(query, pivot, 0, points.size()-1, 0);
   
   
   
}
template<int Dim>
Point<Dim> KDTree<Dim>::FNNHelper(const Point<Dim> & query, int pivpoint, int start, int end, int dim) const{
	if(pivpoint <= 0 || start >= end || start < 0 || end < 0)
		return points[pivpoint];

	

	if(smallerDimVal(query, points[pivpoint],dim)){
		Point<Dim> leftside = FNNHelper(query, (start + pivpoint-1)/2 , start, pivpoint-1, (dim+1)%Dim);
		if(shouldReplace(query, leftside, points[pivpoint])){
			Point<Dim> rightside = FNNHelper(query, (end + pivpoint+1)/2 , pivpoint+1, end, (dim+1)%Dim);
			if(shouldReplace(query, points[pivpoint] , rightside))
				return rightside;
			else
				return points[pivpoint];
		}else
			return leftside;
	}else{
	
		Point<Dim> rightside = FNNHelper(query, (end + pivpoint+1)/2 , pivpoint+1, end, (dim+1)%Dim);
		
		if(shouldReplace(query, rightside, points[pivpoint])){
			Point<Dim> leftside = FNNHelper(query, (start + pivpoint-1)/2 , start, pivpoint-1, (dim+1)%Dim);
			if(shouldReplace(query,   points[pivpoint], leftside))
				return leftside;
			else
				return points[pivpoint];
		}
		else
			return rightside;
			}
	
	/*
	
	
	if(smallerDimVal(query, points[pivpoint],dim)){
		if(shouldReplace(query, FNNHelper(query, (start + pivpoint-1)/2 , 0, pivpoint-1, (dim+1)%Dim), points[pivpoint])){
			return points[pivpoint];
			
		}else
			return FNNHelper(query, (start + pivpoint-1)/2 , 0, pivpoint-1, (dim+1)%Dim);
	}else{
		if(shouldReplace(query, FNNHelper(query,(pivpoint+1+end)/2, pivpoint+1,end, (dim+1)%Dim), points[pivpoint])){
			
				return points[pivpoint];
		}
		else
			return FNNHelper(query,(pivpoint+1+end)/2, pivpoint+1,end, (dim+1)%Dim);
	}
	*/
	/*	

	if(smallerDimVal(query, points[pivpoint],dim)){  
	
		Point<Dim> temp = FNNHelper(query, (start + pivpoint-1)/2 , 0, pivpoint-1, (dim+1)%Dim);
		if(shouldReplace(query, FNNHelper(query, (start + pivpoint-1)/2 , 0, pivpoint-1, (dim+1)%Dim), points[pivpoint]))
				
			return FNNHelper(query,(pivpoint+1+end)/2, pivpoint+1,end, (dim+1)%Dim);
		else
			return temp;
	}else{
		
		Point<Dim> temp = FNNHelper(query,(pivpoint+1+end)/2, pivpoint+1,end, (dim+1)%Dim);
		if(shouldReplace(query, FNNHelper(query,(pivpoint+1+end)/2, pivpoint+1,end, (dim+1)%Dim), points[pivpoint]))
				
			return FNNHelper(query, (start + pivpoint-1)/2 , 0, pivpoint-1, (dim+1)%Dim);
		else
			return temp;
			
	}			
	*/

}
