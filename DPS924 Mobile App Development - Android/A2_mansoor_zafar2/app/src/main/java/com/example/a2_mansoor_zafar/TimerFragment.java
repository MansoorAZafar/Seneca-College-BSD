package com.example.a2_mansoor_zafar;

import android.annotation.SuppressLint;
import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;

import android.os.CountDownTimer;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.TextView;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link TimerFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class TimerFragment extends Fragment {

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    private String recipeTitle = "Empty\nPlease Select an Item first";
    private double total_duration = 5.0;
    private double remainingTime = 5.0;

    private TextView timerTitle, timerCountDown, timerDuration;
    private SeekBar timerSeekBar;
    private ProgressBar timerProgressBar;
    private Button timerBack, timerFinish, timerStart, timerPause, timerReset;
    private CountDownTimer countDownTimer;
    private boolean timerRunning = false;
    private ProgressBar pg;

    public TimerFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment FeedbackFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static TimerFragment newInstance(String param1, String param2) {
        TimerFragment fragment = new TimerFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            this.recipeTitle = getArguments().getString("title");
            this.total_duration = getArguments().getDouble("duration");
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);

            this.remainingTime = this.total_duration * 120 + 0.01;
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_timer, container, false);

        // Set the title of the recipe
        this.timerTitle = view.findViewById(R.id.timer_title);
        this.timerTitle.setText(this.recipeTitle);

        // Set the total duration
        this.timerDuration = view.findViewById(R.id.timer_duration);
        this.timerDuration.setText("Duration: " + this.total_duration + " min");

        // Handle the timer countdown
        this.timerCountDown = view.findViewById(R.id.timer_countdown);
        this.timerCountDown.setText(this.FormatTime(this.total_duration * 60));

        this.timerStart = view.findViewById(R.id.timer_start);
        this.timerStart.setOnClickListener(v -> {
            if (!timerRunning) {
                startCountDown(remainingTime); // Start countdown from remaining time
            }
        });

        this.timerBack = view.findViewById(R.id.timer_back);
        this.timerBack.setOnClickListener(v -> {
            if (this.countDownTimer != null) {
                this.countDownTimer.cancel();
            }
            NavController navController = Navigation.findNavController(view);
            navController.popBackStack();
        });

        this.timerPause = view.findViewById(R.id.timer_pause);
        this.timerPause.setOnClickListener(v -> {
            if (timerRunning) {
                countDownTimer.cancel();
                timerRunning = false; // Update timer state
            }
        });

        pg = view.findViewById(R.id.progressBar);
        pg.setMax((int) (this.total_duration * 60));

        timerSeekBar = view.findViewById(R.id.timer_seekbar);
        timerSeekBar.setMax((int) (this.total_duration * 60)); // Max value in seconds
        timerSeekBar.setProgress((int) (this.total_duration * 60)); // Set initial progress in seconds

        timerSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                remainingTime = progress; // Update remaining time in seconds
                timerCountDown.setText(FormatTime(remainingTime)); // Update countdown display

                // If the timer is running, stop the current timer and restart it with the new time
                if (timerRunning) {
                    countDownTimer.cancel(); // Stop the current timer
                    startCountDown(remainingTime); // Restart the countdown with the new remaining time
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // Optionally, you can stop the timer when user starts tracking
                if (timerRunning) {
                    countDownTimer.cancel();
                    timerRunning = false; // Update timer state
                }
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // Optionally, restart the timer when user stops tracking
                if (!timerRunning && remainingTime > 0) {
                    startCountDown(remainingTime); // Restart countdown if not running
                }
            }
        });

        this.timerFinish = view.findViewById(R.id.timer_Finish);
        this.timerFinish.setOnClickListener(v -> {
            if (this.countDownTimer != null) {
                this.countDownTimer.cancel();
            }
            NavController navController = Navigation.findNavController(view);
            navController.popBackStack();
        });

        this.timerReset = view.findViewById(R.id.timer_restart);
        this.timerReset.setOnClickListener(v -> {
            if(this.countDownTimer != null)
                this.countDownTimer.cancel();
            this.timerRunning = false;
            this.remainingTime = this.total_duration * 60;
            this.timerCountDown.setText(this.FormatTime(this.remainingTime));
            this.timerSeekBar.setProgress((int) (this.total_duration * 60));

            this.timerFinish.setEnabled(false);
            this.timerFinish.setVisibility(View.GONE);
            pg.setProgress(0);

        });

        return view;
    }

        private void startCountDown(double duration) {
            timerRunning = true; // Set the timer state to running

            countDownTimer = new CountDownTimer(timerSeekBar.getProgress() * 1000, 1000) {
                @Override
                public void onTick(long millisUntilFinished) {
                    remainingTime = (int)(millisUntilFinished / 1000.0); // Update remaining time
                    timerCountDown.setText(FormatTime(remainingTime));

                    timerSeekBar.setProgress((int)remainingTime + 1);
                    pg.setProgress((int)remainingTime + 1);
                }

                @Override
                public void onFinish() {
                    timerCountDown.setText("00:00"); // Timer finished UI
                    timerRunning = false; // Update timer state
                    timerSeekBar.setProgress(0);

                    timerFinish.setVisibility(View.VISIBLE);
                    pg.setProgress(pg.getMax());
                    timerFinish.setEnabled(true);
                }
            }.start();
        }

    @SuppressLint("DefaultLocale")
    private String FormatTime(double time) {
        int minutes = (int) time / 60;
        int seconds = (int) time % 60;
        return String.format("%02d:%02d", minutes, seconds);
    }

}




