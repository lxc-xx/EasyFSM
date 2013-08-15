class State
 { 
 	void work()
	{}

	State nextState()
	{
		return this;
	}
}

class StateMachine
{
	public StateMachine()
	{}

	void work()
	{}
	void update()
	{}
}

class StateMachine_Police extends StateMachine
{
	public State current_state;

	void work()
	{
		this.current_state.work();
	}

	void update()
	{
		current_state = current_state.nextState();
	}

	private State STATE_Rest = new State()
	{

		boolean CONDITION_FindThief()
		{
			//Add your code here to define the condition
			return false;
		}

		void work()
		{
			//Add your code here to define the job
		}

		State nextState()
		{
			if( CONDITION_FindThief() )
			{
				return STATE_Run;
			}
			return this;
		}

	};

	private State STATE_Run = new State()
	{

		boolean CONDITION_CatchThief()
		{
			//Add your code here to define the condition
			return false;
		}

		void work()
		{
			//Add your code here to define the job
		}

		State nextState()
		{
			if( CONDITION_CatchThief() )
			{
				return STATE_Rest;
			}
			return this;
		}

	};

}

class StateMachine_Thief extends StateMachine
{
	public State current_state;

	void work()
	{
		this.current_state.work();
	}

	void update()
	{
		current_state = current_state.nextState();
	}

	private State STATE_Rest = new State()
	{

		boolean CONDITION_FindPolice()
		{
			//Add your code here to define the condition
			return false;
		}

		void work()
		{
			//Add your code here to define the job
		}

		State nextState()
		{
			if( CONDITION_FindPolice() )
			{
				return STATE_Run;
			}
			return this;
		}

	};

	private State STATE_Run = new State()
	{

		boolean CONDITION_CaughtByPolice()
		{
			//Add your code here to define the condition
			return false;
		}

		void work()
		{
			//Add your code here to define the job
		}

		State nextState()
		{
			if( CONDITION_CaughtByPolice() )
			{
				return STATE_Rest;
			}
			return this;
		}

	};

}

class StateMachineFactory
{
	public static StateMachine getStateMachine( String name )
	{
		switch( name )
		{
			case "Police":
				return new StateMachine_Police();
			case "Thief":
				return new StateMachine_Thief();
			default:
				return new StateMachine();
		}
	}
}

