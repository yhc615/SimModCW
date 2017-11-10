lambda_k = [1 1/2 1/3];
p_k = []; %probability that item k is requested
for i=1:size(lambda_k,2)
   p_k(i) = lambda_k(i)/sum(lambda_k);
end

% RAND Modelling (CTMC) vs Simulation
Q_RAND = [-1/3 1/6 1/6 1; 1/2 -1 1/2 1; 1/4 1/4 -1/2 1]; % state transition matrix
B_RAND = [0 0 0 1];
P_RAND = B_RAND/Q_RAND; % PQ = B , B = 0 with c index to allow for unique solution to p

%calculate hit ratio
p_hit_RAND = p_k(1)*( P_RAND(1) + P_RAND(3) ) + p_k(2)*( P_RAND(1) + P_RAND(2) ) + p_k(3)*( P_RAND(2) + P_RAND(3) );

RAND_sample = [ 68; 61; 67; 74; 79; 73; 73; 79; 69; 77 ]; %sample results

%Output results
output_txt = "-------------Results for RAND eviction ------------- \nHit Ratio from CTMC modelling: %f \nAverage hit ratio from simulation (10 runs) : %f \n";
fprintf(output_txt, p_hit_RAND, mean(RAND_sample)/100);

%FIFO
Q_FIFO = [-1/3 0 0 0 1/3 0 1; 0 -1/2 1/2 0 0 0 1; 0 0 -1/3 0 0 1/3 1; 0 1 0 -1 0 0 1; 0 0 0 1/2 -1/2 0 1; 1 0 0 0 0 -1 1];
B_FIFO = [0 0 0 0 0 0 1];
P_FIFO = B_FIFO/Q_FIFO;

%calculate hit ratio
p_hit_FIFO = P_FIFO(1)*( p_k(1) + p_k(2) ) + P_FIFO(2)*( p_k(1) + p_k(3) ) + P_FIFO(3)*( p_k(2) + p_k(1) ) + P_FIFO(4)*( p_k(2) + p_k(3) ) + P_FIFO(5)*( p_k(3) + p_k(1) ) + P_FIFO(6)*( p_k(3) + p_k(2) );

FIFO_sample = [70; 73; 73; 62; 76; 69; 70; 70; 69; 70];
output_txt = "-------------Results for FIFO eviction ------------- \nHit Ratio from CTMC modelling: %f \nAverage hit ratio from simulation (10 runs) : %f";
fprintf(output_txt, p_hit_FIFO, mean(FIFO_sample)/100);