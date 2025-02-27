package com.a1;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.content.Intent;
import androidx.fragment.app.Fragment;
import android.os.Bundle;

public class ExploreFragment extends Fragment {

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    public ExploreFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment ExploreFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static ExploreFragment newInstance(String param1, String param2) {
        ExploreFragment fragment = new ExploreFragment();
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
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_explore, container, false);

        Button mailHackMoreInfoButton = view.findViewById(R.id.mailHackMoreInfoButton);
        Button ssdHackMoreInfoButton = view.findViewById(R.id.ssdHackMoreInfoButton);
        Button androidOSHackMoreInfoButton = view.findViewById(R.id.androidOSHackMoreInfoButton);
        Button ctfHackMoreInfoButton = view.findViewById(R.id.ctfHackMoreInfoButton);

        // Set onClickListeners for each button
        mailHackMoreInfoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Implement action for Mail Hackathon button
                Intent intent = new Intent(getActivity(), RegisterHackathonActivity.class);
                intent.putExtra("hackathon_name", "Mail Hackathon");
                startActivity(intent);
            }
        });

        ssdHackMoreInfoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Implement action for SSD Hackathon button
                Intent intent = new Intent(getActivity(), RegisterHackathonActivity.class);
                intent.putExtra("hackathon_name", "SSD Hackathon");
                startActivity(intent);
            }
        });

        androidOSHackMoreInfoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Implement action for Android OS Hackathon button
                Intent intent = new Intent(getActivity(), RegisterHackathonActivity.class);
                intent.putExtra("hackathon_name", "Android OS Hackathon");
                startActivity(intent);
            }
        });

        ctfHackMoreInfoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Implement action for CTF Hackathon button
                Intent intent = new Intent(getActivity(), RegisterHackathonActivity.class);
                intent.putExtra("hackathon_name", "CTF Hackathon");
                startActivity(intent);
            }
        });

        return view;
    }
}