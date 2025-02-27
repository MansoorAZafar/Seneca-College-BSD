package com.example.a2_mansoor_zafar;

import android.content.Intent;
import android.os.Bundle;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.Arrays;
import java.util.List;


/**
 * A simple {@link Fragment} subclass.
 * Use the {@link RecipesFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class RecipesFragment extends Fragment {

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    private final List<RecipeItem> recipeList = Arrays.asList(
            new RecipeItem(
                    R.drawable.baseline_ramen_dining_24,
                    "Ramen Xha",
                    "A delicious ramen recipe with unique ingredients.",
                    "1. Boil water.\n2. Add ramen noodles.\n3. Cook for 5 minutes.\n4. Add seasoning and enjoy!",
                    "Noodles, water, seasoning, vegetables, egg",
                    15.0
            ),
            new RecipeItem(
                    R.drawable.baseline_cake_24,
                    "Cake Ral",
                    "A quick cake recipe with homemade ingredients.",
                    "1. Preheat oven to 350°F.\n2. Mix flour, sugar, and eggs.\n3. Pour into pan and bake for 30 minutes.\n4. Let cool and serve.",
                    "Flour, sugar, eggs, butter, baking powder",
                    45.0
            ),
            new RecipeItem(
                    R.drawable.baseline_rice_bowl_24,
                    "Rice Bowl",
                    "A healthy and tasty rice bowl.",
                    "1. Cook rice.\n2. Sauté vegetables.\n3. Add sauce and mix.\n4. Serve in a bowl and garnish.",
                    "Rice, mixed vegetables, soy sauce, sesame seeds, chicken (optional)",
                    25.0
            ),
            new RecipeItem(
                    R.drawable.baseline_local_pizza_24,
                    "Pizza Delight",
                    "A classic pizza with a modern twist!",
                    "1. Preheat oven to 475°F.\n2. Spread sauce on dough.\n3. Add cheese and toppings.\n4. Bake for 15 minutes.\n5. Slice and serve.",
                    "Pizza dough, tomato sauce, mozzarella, pepperoni, bell peppers, onions",
                    30.0
            )
    );

    private ActivityResultLauncher<Intent> startActivityForResult;

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment FeedbackFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static RecipesFragment newInstance(String param1, String param2) {
        RecipesFragment fragment = new RecipesFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    public RecipesFragment() {
        // Required empty public constructor
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
        return inflater.inflate(R.layout.fragment_recipes, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState)
    {
        super.onViewCreated(view, savedInstanceState);

        this.startActivityForResult = registerForActivityResult(
          new ActivityResultContracts.StartActivityForResult(),
            result -> {
                if(result.getResultCode() == AppCompatActivity.RESULT_OK)
                {
                    NavController navController = Navigation.findNavController(view);
                    Bundle recipe = new Bundle();

                    if (result.getData() != null)
                    {
                        recipe.putString("title", result.getData().getStringExtra("recipe_title"));
                        recipe.putDouble("duration", result.getData().getDoubleExtra("recipe_duration", 0.0));
                    }
                    navController.navigate(R.id.timerFragment, recipe);
                }
            }
        );

        RecyclerView recyclerView = view.findViewById(R.id.recipes_recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(getContext()));

        // Pass the FragmentManager to the adapter
        recyclerView.setAdapter(new RecipeAdapter(recipeList, getActivity(), this.startActivityForResult));


    }
}