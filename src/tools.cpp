#include "tools.h"
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
   * TODO: Calculate the RMSE here.
   */
  
  VectorXd rmse(4);
  rmse << 0,0,0,0;

  // TODO: YOUR CODE HERE
  // check the validity of the following inputs:
  //  * the estimation vector size should not be zero
  //  * the estimation vector size should equal ground truth vector size

  // TODO: accumulate squared residuals
  if (estimations.size() == 0 ||estimations.size() != ground_truth.size()){
     // cout <<"invalid input";
      return rmse;
  }
  for (unsigned i = 0; i < estimations.size(); i++){
    VectorXd res = estimations.at(i) - ground_truth.at(i);       
    //cout<<res<<" res estinamtion "<<estimations.at(i);
    res = res.array() * res.array();   
    //cout<<"multiplication "<< res;
    rmse += res;
   // cout<<"rmse "<< rmse(i);
  }
   
  // TODO: calculate the mean
  rmse = rmse/estimations.size();
  // TODO: calculate the squared root
              
  // return the result
  return rmse.array().sqrt();
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  
  
   MatrixXd Hj(3,4);
  // recover state parameters
  double px = x_state(0);
  double py = x_state(1);
  double vx = x_state(2);
  double vy = x_state(3);

  // pre-compute a set of terms to avoid repeated calculation
  double c1 = px*px+py*py;
  double c2 = sqrt(c1);
  double c3 = (c1*c2);

  // check division by zero
  if (fabs(c1) < 0.0001) {
    return Hj;
  }

  // compute the Jacobian matrix
  Hj << (px/c2), (py/c2), 0, 0,
      -(py/c1), (px/c1), 0, 0,
      py*(vx*py - vy*px)/c3, px*(px*vy - py*vx)/c3, px/c2, py/c2;

  return Hj;
}
