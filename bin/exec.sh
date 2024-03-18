#PBS -N OrudyCellSim
#PBS -l nodes=1:ppn=1
#PBS -l walltime=20000:00:00
#PBS -e stderr.log
#PBS -o stdout.log
#Specific the shell types
#PBS -S /bin/bash
#Specific the queue type
#PBS -q dque

cd $PBS_O_WORKDIR
NPROCS=`wc -l < $PBS_NODEFILE`
echo This job has allocated $NPROCS nodes

# Use this to export the library path
export LD_LIBRARY_PATH=/opt/prog/sundial/lib64:$LD_LIBRARY_PATH

mpirun -machinefile $PBS_NODEFILE -np $NPROCS ./orudy_cell_sim
