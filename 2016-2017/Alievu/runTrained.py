from sklearn.externals import joblib
import gym
import numpy as np
import utils as u
from sklearn import preprocessing
from sklearn.linear_model import SGDRegressor
dump_path = u.dump_path

algo = joblib.load(dump_path + 'pretrained.pkl')

env = gym.make('SpaceInvaders-v0')
env.monitor.start("/tmp/gym-results", force=True)

nframes = 5

records_counter = 0
for episode in range(4):
    print('---episode ' + str(episode))
    # PREPARE FIRST STEPS
    observation = env.reset()
    n_frames_reward = 0.;
    rewards = np.array([0.]);
    train_data_n_frames = np.hstack((u.to1D(observation), 10))
    # fill first 'nframes' steps
    for step in range(nframes):
        action = env.action_space.sample()
        before_action_observation = observation
        observation, reward, done, info = env.step(action)
        n_frames_reward += reward
        rewards = np.hstack((rewards, reward))
        train_data_n_frames = u.concatNewStep(train_data_n_frames,
                                              before_action_observation,
                                              action)
    #input('---Press any key...')
    train_data_n_frames = train_data_n_frames[1:]
    rewards = rewards[1:]
    print('---preparations finished')

    for step in range(10000 - nframes):
        print('---step ' + str(step))
        # reactive learning
        if (n_frames_reward > 0):
            algo.partial_fit(preprocessing.normalize([u.to1D(train_data_n_frames)]), [n_frames_reward])
        # forget the oldest
        train_data_n_frames = train_data_n_frames[1:]
        n_frames_reward -= rewards[0]
        rewards = rewards[1:]
        
        # try predict all actions
        action = 0
        curr_max_reward_for_action = 0.;
        before_action_observation = observation
        for try_action in range(env.action_space.n):
            try_data = u.concatNewStep(train_data_n_frames,
                                       observation,
                                       try_action)
            predicted = algo.predict(preprocessing.normalize([u.to1D(try_data)]))[0]
            if (try_action == 0):
                curr_max_reward_for_action = predicted
            print(predicted)
            if (predicted > curr_max_reward_for_action):
                action = try_action
                curr_max_reward_for_action = predicted
        #print(curr_max_reward_for_action)
        #input()
        observation, reward, done, info = env.step(action)
        print('\naction: (' + str(action) + ') reward: ' + str(reward))
        n_frames_reward += reward
        rewards = np.hstack((rewards, reward))
        
        train_data_n_frames = u.concatNewStep(train_data_n_frames,
                                              before_action_observation,
                                              action)
        if done:
            print("---Episode finished after {} timesteps".format(step+1))
            break

env.monitor.close()
#gym.upload("/tmp/gym-results", api_key="sk_uuyOTK73Sh2HfWZekdb1XQ")
