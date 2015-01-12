namespace FigaroLib.Helpers
{

    public class Timer
    {
        #region members

        private double timeCounter = 0;
        private double maxTime;

        #endregion

        public Timer(double maxTime)
        {
            this.maxTime = maxTime;
        }

        public bool update(double step)
        {
            timeCounter += step;
            if (timeCounter >= maxTime)
            {
                timeCounter = 0;
                return true;
            }
            return false;
        }

        public void reset()
        {
            timeCounter = 0;
        }

        public void setMaxTime(double maxTime)
        {
            this.maxTime = maxTime;
        }
    }
}
