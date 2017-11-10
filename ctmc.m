Q = [-1/3 1/6 1/6 1; 1/2 -1 1/2 1; 1/4 1/4 -1/2 1]; % state transition matrix
B = [0 0 0 1];
lambda_k = [1 1/2 1/3];
p_k = []; %probability that item k is requested
for i=1:size(lambda_k,2)
   p_k(i) = lambda_k(i)/sum(lambda_k);
end

P = B/Q; % PQ = B , B = 0 with c index to allow for unique solution to p

%calculate hit ratio
p_hit = p_k(1)*( P(1) + P(3) ) + p_k(2)*( P(1) + P(2) ) + p_k(3)*( P(2) + P(3) );

Sample = [ 68; 61; 67; 74; 79; 73; 73; 79; 69; 77 ]; %sample results

%Output results
output_txt = "Hit Ratio from CTMC modelling: %f \nAverage hit ratio from simulation (10 runs) : %f";
fprintf(output_txt, p_hit, mean(Sample)/100);
