int size = 101;  //TODO
Eigen::MatrixXf TransitionMatrix(size, size);
Eigen::VectorXf v(size);

unsigned int ROLLS = 100; //TODO

double prob = 1.0/6.0;  //TODO




void SetTransitionMatrix()
{
	TransitionMatrix.setZero();
	{
		for (int i = 0; i < TransitionMatrix.rows() - 6; i++) 
		{

			TransitionMatrix(i, i + 1) = prob;
			TransitionMatrix(i, i + 2) = prob;
			TransitionMatrix(i, i + 3) = prob;
			TransitionMatrix(i, i + 4) = prob;
			TransitionMatrix(i, i + 5) = prob;
			TransitionMatrix(i, i + 6) = prob;




		}
		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 1) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 2) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 3) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 4) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 6, TransitionMatrix.rows() - 6 + 5) = prob * 2;

		TransitionMatrix(TransitionMatrix.rows() - 5, TransitionMatrix.rows() - 5 + 1) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 5, TransitionMatrix.rows() - 5 + 2) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 5, TransitionMatrix.rows() - 5 + 3) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 5, TransitionMatrix.rows() - 5 + 4) = prob * 3;

		TransitionMatrix(TransitionMatrix.rows() - 4, TransitionMatrix.rows() - 4 + 1) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 4, TransitionMatrix.rows() - 4 + 2) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 4, TransitionMatrix.rows() - 4 + 3) = prob * 4;

		TransitionMatrix(TransitionMatrix.rows() - 3, TransitionMatrix.rows() - 3 + 1) = prob;
		TransitionMatrix(TransitionMatrix.rows() - 3, TransitionMatrix.rows() - 3 + 2) = prob * 5;

		TransitionMatrix(TransitionMatrix.rows() - 2, TransitionMatrix.rows() - 2 + 1) = prob * 6;

		TransitionMatrix(TransitionMatrix.rows() - 1, TransitionMatrix.rows() - 1) = prob * 6;
	/*
	}	
	for (int i = 0; i < TransitionMatrix.rows(); i++)
	{
		//Ladders
		// 3-19
		if (TransitionMatrix(i, 3) > 0)
		{
			TransitionMatrix(i, 19) = TransitionMatrix(i, 19) + TransitionMatrix(i, 3);
			TransitionMatrix(i, 3) = 0;
		}
		// 15-37
		if (TransitionMatrix(i, 15) > 0)
		{
			TransitionMatrix(i, 37) = TransitionMatrix(i, 37) + TransitionMatrix(i, 15);
			TransitionMatrix(i, 15) = 0;
		}
		// 22-42
		if (TransitionMatrix(i, 22) > 0)
		{
			TransitionMatrix(i, 42) = TransitionMatrix(i, 42) + TransitionMatrix(i, 22);
			TransitionMatrix(i, 22) = 0;
		}
		//  25-64
		if (TransitionMatrix(i, 25) > 0)
		{
			TransitionMatrix(i, 64) = TransitionMatrix(i, 64) + TransitionMatrix(i, 25);
			TransitionMatrix(i, 25) = 0;
		}
		//  41-73
		if (TransitionMatrix(i, 41) > 0)
		{
			TransitionMatrix(i, 73) = TransitionMatrix(i, 73) + TransitionMatrix(i, 41);
			TransitionMatrix(i, 41) = 0;
		}
		//53=74
		if (TransitionMatrix(i, 53) > 0)
		{
			TransitionMatrix(i, 74) = TransitionMatrix(i, 74) + TransitionMatrix(i, 53);
			TransitionMatrix(i, 53) = 0;
		}
		//63-86
		if (TransitionMatrix(i, 63) > 0)
		{
			TransitionMatrix(i, 86) = TransitionMatrix(i, 86) + TransitionMatrix(i, 63);
			TransitionMatrix(i, 63) = 0;
		}
		//76-91
		if (TransitionMatrix(i, 76) > 0)
		{
			TransitionMatrix(i, 91) = TransitionMatrix(i, 91) + TransitionMatrix(i, 76);
			TransitionMatrix(i, 76) = 0;
		}
		//84-98
		if (TransitionMatrix(i, 84) > 0)
		{
			TransitionMatrix(i, 98) = TransitionMatrix(i, 98) + TransitionMatrix(i, 84);
			TransitionMatrix(i, 84) = 0;
		}
		//SNAKES
		//11-7
		if (TransitionMatrix(i, 11) > 0)
		{
			TransitionMatrix(i, 7) = TransitionMatrix(i, 7) + TransitionMatrix(i, 11);
			TransitionMatrix(i, 11) = 0;
		}
		//18-13
		if (TransitionMatrix(i, 18) > 0)
		{
			TransitionMatrix(i, 13) = TransitionMatrix(i, 13) + TransitionMatrix(i, 18);
			TransitionMatrix(i, 18) = 0;
		}
		//28-12
		if (TransitionMatrix(i, 28) > 0)
		{
			TransitionMatrix(i, 12) = TransitionMatrix(i, 12) + TransitionMatrix(i, 28);
			TransitionMatrix(i, 28) = 0;
		}
		//36-34
		if (TransitionMatrix(i, 36) > 0)
		{
			TransitionMatrix(i, 34) = TransitionMatrix(i, 34) + TransitionMatrix(i, 36);
			TransitionMatrix(i, 36) = 0;
		}
		//77-16
		if (TransitionMatrix(i, 77) > 0)
		{
			TransitionMatrix(i, 16) = TransitionMatrix(i, 16) + TransitionMatrix(i, 77);
			TransitionMatrix(i, 77) = 0;
		}
		//47-26
		if (TransitionMatrix(i, 47) > 0)
		{
			TransitionMatrix(i, 26) = TransitionMatrix(i, 26) + TransitionMatrix(i, 47);
			TransitionMatrix(i, 47) = 0;
		}
		//83-29
		if (TransitionMatrix(i, 83) > 0)
		{
			TransitionMatrix(i, 39) = TransitionMatrix(i, 39) + TransitionMatrix(i, 83);
			TransitionMatrix(i, 83) = 0;
		}
		//92-75
		if (TransitionMatrix(i, 92) > 0)
		{
			TransitionMatrix(i, 75) = TransitionMatrix(i, 75) + TransitionMatrix(i, 92);
			TransitionMatrix(i, 92) = 0;
		}
		//99-70
		if (TransitionMatrix(i, 99) > 0)
		{
			TransitionMatrix(i, 70) = TransitionMatrix(i, 70) + TransitionMatrix(i, 99);
			TransitionMatrix(i, 99) = 0;
		}
		*/
	}
	//TransitionMatrix(size - 1, size - 1) = 1;
	//std::ofstream myfile;
	//myfile.open("Check.txt");
	//myfile << TransitionMatrix;
	//myfile.close();
	//std::cout << TransitionMatrix << std::endl;
	//exit(1);

}

// If the 0 row is not on the board then need to stay on the board at the last row
		
//}